#!/bin/sh
#
# Third-party sources kept under vendor/. Each one is a copy of part of a
# release of its upstream repository, committed to this repository with no
# change, and vendor/<name>.lock records where it comes from: the repository,
# the tag, the commit the tag pointed to, the paths that were taken, and the
# SHA-256 of every file that the copy holds.
#
# Usage: vendor.sh fetch <name> [tag]
#        vendor.sh verify <name> [--upstream]
#
#   fetch    replaces vendor/<name> with the paths of the lock file as they are
#            at the tag, and rewrites the lock file. With no tag it takes the
#            one of the lock file, which reproduces the copy.
#   verify   checks that vendor/<name> holds the files of the lock file, with
#            their hashes, and no other file. With --upstream it clones the
#            repository as well and checks that the tag still points to the
#            commit of the lock file and that its files have those hashes.
#
# The paths of a lock file are files or directories of the upstream
# repository. A directory stands for every file below it.

set -eu

usage() {
    echo "usage: vendor.sh fetch <name> [tag]" >&2
    echo "       vendor.sh verify <name> [--upstream]" >&2
    exit 2
}

[ $# -ge 2 ] || usage

COMMAND="$1"
NAME="$2"
ARGUMENT="${3:-}"

HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/../.." && pwd)
LOCK="$ROOT/vendor/$NAME.lock"
COPY="$ROOT/vendor/$NAME"

[ -f "$LOCK" ] || { echo "vendor.sh: $LOCK not found" >&2; exit 1; }

if command -v sha256sum > /dev/null 2>&1; then
    sha256() { sha256sum "$1" | cut -d ' ' -f 1; }
else
    sha256() { shasum -a 256 "$1" | cut -d ' ' -f 1; }
fi

# | A field of the lock file that fits in its line.
field() {
    sed -n "s/^$1: *//p" "$LOCK" | head -1
}

# | The lines of a section of the lock file, the ones indented below its name
# up to the next line that starts at the left margin.
section() {
    awk -v name="$1:" '
        $0 == name { inside = 1; next }
        /^[^ ]/    { inside = 0 }
        inside && NF { sub(/^ +/, ""); print }
    ' "$LOCK"
}

# | The files below a directory, one per line and relative to it, with their
# hashes in front, in the order of the C locale.
hashes() {
    (cd "$1" && find . -type f | sed 's|^\./||' | LC_ALL=C sort) |
    while IFS= read -r file; do
        echo "$(sha256 "$1/$file")  $file"
    done
}

# | A clone of the upstream repository at a tag, with the files as the
# repository stores them.
clone() {
    git -c advice.detachedHead=false -c core.autocrlf=false \
        clone --quiet --depth 1 --branch "$2" "$1" "$3"
}

# | Copies the paths of the lock file from a clone to a directory.
take() {
    section paths | while IFS= read -r path; do
        [ -e "$1/$path" ] || { echo "vendor.sh: $path is not in the tag" >&2; exit 1; }
        git -C "$1" ls-files -- "$path" | while IFS= read -r file; do
            mkdir -p "$2/$(dirname "$file")"
            cp "$1/$file" "$2/$file"
        done
    done
}

SOURCE=$(field source)
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT

case "$COMMAND" in

fetch)
    TAG="${ARGUMENT:-$(field tag)}"
    clone "$SOURCE" "$TAG" "$WORK/upstream"
    COMMIT=$(git -C "$WORK/upstream" rev-parse HEAD)
    take "$WORK/upstream" "$WORK/copy"
    {
        sed -n '/^#/p' "$LOCK"
        echo "source: $SOURCE"
        echo "tag: $TAG"
        echo "commit: $COMMIT"
        echo "paths:"
        section paths | sed 's/^/  /'
        echo "files:"
        hashes "$WORK/copy" | sed 's/^/  /'
    } > "$WORK/lock"
    rm -rf "$COPY"
    mv "$WORK/copy" "$COPY"
    mv "$WORK/lock" "$LOCK"
    echo "vendor/$NAME: $TAG ($COMMIT), $(section files | wc -l | tr -d ' ') files"
    ;;

verify)
    section files > "$WORK/expected"
    [ -d "$COPY" ] || { echo "vendor.sh: $COPY not found" >&2; exit 1; }
    hashes "$COPY" > "$WORK/actual"
    if ! diff "$WORK/expected" "$WORK/actual" > "$WORK/diff"; then
        echo "vendor/$NAME does not match vendor/$NAME.lock:" >&2
        cat "$WORK/diff" >&2
        exit 1
    fi
    if [ "$ARGUMENT" = "--upstream" ]; then
        TAG=$(field tag)
        clone "$SOURCE" "$TAG" "$WORK/upstream"
        COMMIT=$(git -C "$WORK/upstream" rev-parse HEAD)
        if [ "$COMMIT" != "$(field commit)" ]; then
            echo "vendor/$NAME: the tag $TAG points to $COMMIT, not to $(field commit)" >&2
            exit 1
        fi
        take "$WORK/upstream" "$WORK/copy"
        hashes "$WORK/copy" > "$WORK/upstream.hashes"
        if ! diff "$WORK/expected" "$WORK/upstream.hashes" > "$WORK/diff"; then
            echo "vendor/$NAME.lock does not match the tag $TAG of $SOURCE:" >&2
            cat "$WORK/diff" >&2
            exit 1
        fi
    fi
    echo "vendor/$NAME: $(wc -l < "$WORK/expected" | tr -d ' ') files, $(field tag)"
    ;;

*)
    usage
    ;;

esac
