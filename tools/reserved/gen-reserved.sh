#!/bin/sh
#
# Names that a platform takes for itself, the ones a Termina identifier may not
# reuse. A generated .c includes nothing but <termina.h>, so what it collides
# with is whatever that one header drags in: the OSAL API, the standard headers
# it uses, and everything those pull behind them. The probe below is that
# translation unit, compiled by the platform's own compiler with the platform's
# own flags, which is where index() comes from on posix-gcc and rtems5.
#
# Two extractions:
#
#   the declarations, from -aux-info under gcc and from the AST dump under
#   clang, which has no -aux-info
#   -E -dM, every macro that survives the preprocessor
#
# The gcc path reports functions alone, so the typedef names and the objects of
# the standard are left to the fixed list of Semantic/Reserved.hs, where they
# belong anyway because they do not change from platform to platform.
#
# Identifiers that start with an underscore are dropped: the rule about them is
# a pattern in the fixed list, so carrying a few hundred __builtin_* names as
# data buys nothing. The names of this code base, termina__* and TERMINA__* plus
# the include guards, go out for the same reason.
#
# A second list holds the global symbols of what a deployment links, which no
# header has to declare: the start label of the BSP of the LEON3, the kernel of
# FreeRTOS, the functions of RTEMS that <termina.h> does not reach. The sources
# of the OSAL, those of a test build among them, are compiled with the flags of
# the platform and linked with -Wl,--trace, which names every object and library
# that the linker opens; nm reads the defined globals out of all of them. An
# identifier that starts with an underscore and a lowercase letter stays in this
# list, because a parameter may take that shape and newlib defines _write. It
# needs the GNU linker.
#
# The output is the module Semantic.Reserved.<Platform> of the transpiler, with
# the two lists and the SHA-256 of every file that the linker opened.
#
# Usage: gen-reserved.sh <platform> [output]
#
#   ./gen-reserved.sh posix-gcc
#   TERMINA_OSAL_DIR=/opt/termina-osal ./gen-reserved.sh rtems5-leon3sf-nexysa7 RTEMS5LEON3SFNEXYSA7.hs
#
# EXTRA_CFLAGS goes after the flags of the platform, to see what a define of
# one's own changes: with -D_DEFAULT_SOURCE newlib and glibc declare the names
# of POSIX that they hide otherwise, index() among them.
#
# RESERVED_ORIGIN, when set, goes into the header as the place where the list
# was generated, such as the tag of the image.
#
# The three platforms need their three toolchains, so the lists that are
# committed come from the docker-termina image, which pins all of them together
# with the OSAL.

set -eu

PLATFORM="${1:?usage: gen-reserved.sh <platform> [output]}"
OUTPUT="${2:-}"

HERE=$(cd "$(dirname "$0")" && pwd)
TERMINA_OSAL_DIR="${TERMINA_OSAL_DIR:-/opt/termina-osal}"
export TERMINA_OSAL_DIR

ask() {
    make -s -f "$HERE/probe.mk" PLATFORM="$PLATFORM" "print-$1" | tail -1
}

# | The settings of a test build, whose OSAL carries the test runtime as well.
askTest() {
    make -s -f "$HERE/probe.mk" PLATFORM="$PLATFORM" TERMINA_TEST=1 "print-$1" | tail -1
}

case "$PLATFORM" in
    posix-gcc) MODULE=POSIXGCC ;;
    rtems5-leon3sf-nexysa7) MODULE=RTEMS5LEON3SFNEXYSA7 ;;
    freertos10-stm32l432-nucleol432kc) MODULE=FreeRTOS10STM32L432NUCLEOL432KC ;;
    rtems6-zynq7000-pynqz2) MODULE=RTEMS6ZYNQ7000PYNQZ2 ;;
    rtems6-rv32im-spike) MODULE=RTEMS6RV32IMSPIKE ;;
    rtems6-noel32im-artya7) MODULE=RTEMS6NOEL32IMARTYA7 ;;
    *) echo "gen-reserved.sh: unknown platform $PLATFORM" >&2; exit 1 ;;
esac

CC=$(ask CC)
CFLAGS="$(ask CFLAGS) ${EXTRA_CFLAGS:-}"
INCLUDE_DIRS=$(ask INCLUDE_DIRS)

WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT

echo '#include <termina.h>' > "$WORK/probe.c"

# | termina.h opens with the config.h that a build generates for its project.
# The probe declares no object of its own, so the counters are all zero.
cat > "$WORK/config.h" <<'EOF'
#ifndef CONFIG_H__
#define CONFIG_H__
#define TERMINA__APP_CONFIG__POOLS 0
#define TERMINA__APP_CONFIG__TASKS 0
#define TERMINA__APP_CONFIG__PERIODIC_TIMERS 0
#define TERMINA__APP_CONFIG__MUTEXES 0
#define TERMINA__APP_CONFIG__MESSAGE_QUEUES 0
#define TERMINA__APP_CONFIG__MESSAGE_BUFFER_MEMORY 0
#define TERMINA__APP_CONFIG__IRQ_LOCKS 0
#define TERMINA__APP_CONFIG__EXCEPT_PROTECTED 0
#define TERMINA__TIME__MICROSECONDS_PER_TICK 10000
#define TERMINA__INTERRUPT__NUMBER_OF_INTERRUPTS 0
#endif
EOF

INCS="-I$WORK"
for dir in $INCLUDE_DIRS; do
    INCS="$INCS -I$dir"
done

if $CC --version | head -1 | grep -qi clang; then
    # shellcheck disable=SC2086
    $CC $CFLAGS $INCS -fsyntax-only -Xclang -ast-dump "$WORK/probe.c" > "$WORK/decls.txt"
    # | One line per declaration of the unit, the ones of the top level flush
    # against the left margin. The name is the last token before the type,
    # which the dump prints quoted.
    sed -n "s/^[|\`]-[A-Za-z]*Decl [^']* \([A-Za-z_][A-Za-z0-9_]*\) '.*\$/\1/p" \
        "$WORK/decls.txt" > "$WORK/decls.names"
else
    # shellcheck disable=SC2086
    $CC $CFLAGS $INCS -fsyntax-only -aux-info "$WORK/decls.aux" "$WORK/probe.c"
    # | The name is the first identifier of the declaration that an opening
    # parenthesis follows, as long as that parenthesis does not open a pointer
    # declarator. A parameter that is a pointer to a function brings
    # parentheses of its own after the name, and a function that returns a
    # pointer to a function has its name inside a declarator that starts with
    # an asterisk.
    awk '/\*\/ extern / {
            sub(/^.*\*\/ extern /, "")
            if (match($0, /[A-Za-z_][A-Za-z0-9_]* *\([^*]/)) {
                name = substr($0, RSTART, RLENGTH)
                sub(/ *\(.*$/, "", name)
                print name
            }
         }' "$WORK/decls.aux" > "$WORK/decls.names"
fi

# shellcheck disable=SC2086
$CC $CFLAGS $INCS -E -dM "$WORK/probe.c" > "$WORK/macros.txt"

{
    cat "$WORK/decls.names"
    sed -n 's/^#define \([A-Za-z_][A-Za-z0-9_]*\).*$/\1/p' "$WORK/macros.txt"
} | grep -v '^_' \
  | grep -vE '^(termina|TERMINA)__' \
  | grep -vE '^[A-Z][A-Za-z0-9_]*_H__$' \
  | sort -u > "$WORK/names.txt"

# | The linked symbols. The nm of the toolchain sits next to its gcc.
NM=$(echo "$CC" | sed 's/gcc$/nm/')
TEST_CFLAGS="$(askTest CFLAGS) ${EXTRA_CFLAGS:-}"
# | The link map of the platform is named after the target of make, and the
# probe needs none.
LDFLAGS=$(askTest LDFLAGS | tr ' ' '\n' | grep -v '^-Wl,-Map=' | tr '\n' ' ')

# | The tables of the OSAL take their size from these counters, and a table of
# size zero does not compile under -pedantic-errors.
mkdir "$WORK/obj" "$WORK/osal"
sed 's/ 0$/ 1/' "$WORK/config.h" > "$WORK/osal/config.h"
OSAL_INCS=$(echo "$INCS" | sed "s|-I$WORK |-I$WORK/osal |")

n=0
for src in $(askTest OSAL_SRCS); do
    n=$((n + 1))
    # shellcheck disable=SC2086
    $CC $TEST_CFLAGS $OSAL_INCS -c "$src" -o "$WORK/obj/$n.o"
done

# | The OSAL refers to the functions that the generated code defines, which the
# probe does not have, so the link leaves them unresolved.
# shellcheck disable=SC2086
$CC $TEST_CFLAGS "$WORK"/obj/*.o $LDFLAGS -Wl,--trace -Wl,--unresolved-symbols=ignore-all \
    -o "$WORK/probe.elf" > "$WORK/trace.txt"

# | A member of an archive is traced as the archive and the member between
# parentheses; the archive is the file that counts.
grep -o '/[^ ()]*\.\(o\|a\|so[.0-9]*\)' "$WORK/trace.txt" | grep -v "^$WORK/" \
  | xargs realpath | sort -u > "$WORK/linked.files"

{
    for obj in "$WORK"/obj/*.o; do
        "$NM" -g --defined-only "$obj"
    done
    # | libc.so and libgcc_s.so are scripts of the linker that name the shared
    # objects, which the trace lists as well; nm does not read them.
    while read -r file; do
        case "$file" in
            *.so*) "$NM" -D --defined-only "$file" 2>/dev/null || true ;;
            *) "$NM" -g --defined-only "$file" 2>/dev/null || true ;;
        esac
    done < "$WORK/linked.files"
} | awk 'NF == 3 { print $3 }' | sed 's/@.*$//' \
  | grep -E '^[A-Za-z_][A-Za-z0-9_]*$' \
  | grep -vE '^_[A-Z_]' \
  | grep -vE '^(termina|TERMINA)__' \
  | grep -vxE 'system_entry|system_except|test_checks|test_clock|test_scenario' \
  | sort -u > "$WORK/symbols.txt"

# | A symbol that a header already declares is in the first list.
comm -23 "$WORK/symbols.txt" "$WORK/names.txt" > "$WORK/linked.txt"

haskellList() {
    awk 'NR == 1 { printf "  [ \"%s\"\n", $0; next } { printf "  , \"%s\"\n", $0 } END { print "  ]" }' "$1"
}

emit() {
    echo "-- | Names that the $PLATFORM platform takes for itself."
    echo "--"
    echo "-- Generated by tools/reserved/gen-reserved.sh of termina-osal, which compiles a"
    echo "-- translation unit that includes <termina.h> with the compiler and the flags of"
    echo "-- the platform and collects every declaration and macro it sees, and reads the"
    echo "-- global symbols of the OSAL and of everything the linker opens for it."
    echo "-- Regenerate it instead of editing it by hand."
    echo "--"
    if [ -n "${RESERVED_ORIGIN:-}" ]; then
        echo "-- Origin: $RESERVED_ORIGIN"
    fi
    echo "-- Compiler: $($CC --version | head -1)"
    echo "-- Flags: $CFLAGS" | sed 's/ *$//'
    echo "-- Linked:"
    while read -r file; do
        echo "--   $(sha256sum "$file" | cut -c1-64)  $file"
    done < "$WORK/linked.files"
    echo "module Semantic.Reserved.$MODULE (reservedNames, linkedNames) where"
    echo
    echo "import qualified Data.Set as S"
    echo "import Core.AST (Identifier)"
    echo
    echo "reservedNames :: S.Set Identifier"
    echo "reservedNames = S.fromList"
    haskellList "$WORK/names.txt"
    echo
    echo "linkedNames :: S.Set Identifier"
    echo "linkedNames = S.fromList"
    haskellList "$WORK/linked.txt"
}

if [ -n "$OUTPUT" ]; then
    emit > "$OUTPUT"
    echo "$OUTPUT: $(wc -l < "$WORK/names.txt" | tr -d ' ') names, $(wc -l < "$WORK/linked.txt" | tr -d ' ') linked"
else
    emit
fi
