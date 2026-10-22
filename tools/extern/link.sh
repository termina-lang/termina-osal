#!/bin/sh
# Links the C of a Termina project (the objects of its extern sources and its
# static libraries) into a single relocatable object in which only the extern
# functions stay global, and checks it.
#
# Usage: link.sh OUT "OBJS" "LIBS" "SYMBOLS"
#
#   OUT      relocatable object to produce
#   OBJS     objects of the extern C sources
#   LIBS     static libraries of the selected platform
#   SYMBOLS  names of the extern functions declared in the project
#
# The toolchain comes from the environment: CC, CFLAGS, LD, OBJCOPY, NM and
# OBJDUMP, and LIBC, the file name of the C library that the platform links.
#
# The object format is the one of the compiler: Mach-O when its target is
# Darwin, ELF otherwise. On Mach-O the linker hides the symbols itself and the
# names carry a leading underscore; on ELF objcopy hides them.

set -eu

out=$1
objs=$2
libs=$3
symbols=$4

fail() {
    printf '[error]: %s\n' "$1" >&2
    exit 1
}

# A failure, through fail or set -e, leaves no object for make to take as up to date.
trap 'status=$?; [ "$status" -eq 0 ] || rm -f "$out"; rm -f "$out.syms"' EXIT

case "$($CC -dumpmachine)" in
    *darwin*) format=macho; prefix=_ ;;
    *) format=elf; prefix= ;;
esac

# Global symbols defined with strong binding by the given files, one per line
# as "name<TAB>file"
defined() {
    [ -n "$1" ] || return 0
    # shellcheck disable=SC2086
    $NM -P -g -A $1 | awk -v prefix="$prefix" '
        $3 ~ /^[TDBRGS]$/ {
            file = $1; sub(/:$/, "", file)
            name = $2; if (prefix != "") sub("^" prefix, "", name)
            print name "\t" file
        }'
}

# 1. No global of the C sources is also defined by a library: the linker would
# take the one of the source silently, and the library would call it.
duplicated=$( { defined "$objs" | sed 's/^/o\t/'; defined "$libs" | sed 's/^/l\t/'; } | awk -F '\t' '
    $1 == "o" { o[$2] = $3 }
    $1 == "l" { l[$2] = $3 }
    END { for (s in o) if (s in l) printf "%s (%s and %s) ", s, o[s], l[s] }')
[ -z "$duplicated" ] || fail "defined by an extern source and by an extern library: $duplicated"

# 2. Partial link. -u pulls from the libraries the members that define an extern
# function declared directly, without a wrapper.
for s in $symbols; do
    printf '%s%s\n' "$prefix" "$s"
done > "$out.syms"
undefine=
for s in $symbols; do
    undefine="$undefine -u $prefix$s"
done
# shellcheck disable=SC2086
if [ "$format" = macho ]; then
    $LD -r -exported_symbols_list "$out.syms" $undefine $objs $libs -o "$out"
else
    $LD -r $undefine $objs $libs -o "$out"
fi

# 3. Every extern function is defined.
present=$(defined "$out" | cut -f 1)
missing=
for s in $symbols; do
    printf '%s\n' "$present" | grep -qxF "$s" || missing="$missing $s"
done
[ -z "$missing" ] || fail "extern functions not defined by the extern C:$missing"

# 4. What is left undefined is defined by the C library or by libgcc: the C does
# not call into Termina, the OSAL or the RTOS. On Mach-O the C library is
# libSystem, whose symbols the SDK lists in text stubs, and it holds libgcc's
# counterpart (compiler_rt) as well.
if [ "$format" = macho ]; then
    sdk=$(xcrun --show-sdk-path)
    libraries=$(ls "$sdk"/usr/lib/system/*.tbd)
else
    # shellcheck disable=SC2086
    libraries="$($CC $CFLAGS -print-file-name="$LIBC") $($CC $CFLAGS -print-libgcc-file-name)"
fi
for library in $libraries; do
    [ -f "$library" ] || fail "cannot find the C library of the toolchain: $library"
done
# shellcheck disable=SC2086
allowed=$($NM -P -g -A $libraries 2>/dev/null | awk '{ sub(/^.*: /, "") } $2 != "U" && $2 != "w" { print $1 }' | sort -u)
outside=$($NM -P -u "$out" | awk '{ print $1 }' | sort -u | while read -r s; do
    printf '%s\n' "$allowed" | grep -qxF "$s" || printf '%s ' "${s#"$prefix"}"
done)
[ -z "$outside" ] || fail "the extern C uses symbols outside the C library and libgcc: $outside"

# 5. No constructors or destructors, which would run before the initialization
# of Termina. 6. No mutable state: an extern function keeps none.
if [ "$format" = macho ]; then
    ctors='^__(mod_init_func|mod_term_func|init_offsets)$'
    state='^__(data|bss|common)$'
else
    ctors='^\.(init_array|fini_array|ctors|dtors)(\.|$)'
    state='^\.(data|bss|sdata|sbss)(\.|$)'
fi
sections=$($OBJDUMP -h "$out" | awk '$1 ~ /^[0-9]+$/ { print $2 " " $3 }')
found=$(printf '%s\n' "$sections" | awk -v re="$ctors" '$1 ~ re { printf "%s ", $1 }')
[ -z "$found" ] || fail "the extern C has constructors or destructors: $found"
found=$(printf '%s\n' "$sections" | awk -v re="$state" '$1 ~ re && $2 !~ /^0+$/ { printf "%s ", $1 }')
[ -z "$found" ] || fail "the extern C has mutable state: $found"

# 7. Only the extern functions stay global, and with none every symbol becomes
# local (objcopy fails without a message on an empty --keep-global-symbols).
if [ "$format" = elf ]; then
    if [ -n "$symbols" ]; then
        $OBJCOPY --keep-global-symbols="$out.syms" "$out"
    else
        $OBJCOPY -w --localize-symbol='*' "$out"
    fi
fi
