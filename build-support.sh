#!/bin/bash
#
# build-support.sh -- build the vendored EPICS 3.14 support modules.
#
# Runs inside the build container, before the IOC itself is built.
#
# The trick here is that NOTHING gets its configure/RELEASE edited. Every
# module -- and ag/mk itself -- points at the production paths:
#
#     /gem_sw/epics/R3.14.12.8/base                 (epics-base-314 RPM)
#     /gem_sw/targetOS/RTEMS/rtems-4.10             (rtems410 RPM)
#     /gem_sw/prod/R3.14.12.8/support/<mod>/<ver>   (vendored here)
#
# The first two are installed at exactly those paths by their RPMs. For the
# third we symlink each vendored module into place, so a module's own RELEASE
# resolves to the copy in this repo. The result is that the tree builds
# identically here, in CI, and on a developer's NFS-mounted workstation, and
# the sources stay byte-identical to what production was built from.

set -euo pipefail

# --stage-only re-points the symlinks and stops, without rebuilding.
#
# This exists because the repo is mounted at a DIFFERENT path in each context:
# build_rpm.sh mounts it at /work, dev_environment.sh at /repo. Symlinks baked
# in during the RPM build therefore dangle inside the dev container. Re-running
# this with --stage-only fixes them in about a second, and is the first thing
# to do after entering the dev container.
STAGE_ONLY=0
[ "${1:-}" = "--stage-only" ] && STAGE_ONLY=1

TOP="$(cd "$(dirname "$0")" && pwd)"
SUPPORT_SRC="$TOP/support"
PRODSUP="/gem_sw/prod/R3.14.12.8/support"

# The Gemini build hosts set this in the login environment, and
# gemUtil/1-14's configure/CONFIG_SITE reads it:
#     EPICS_RELEASE = $(shell echo "${GEM_EPICS_RELEASE}")
# Unset, that overrides the R3.14.12.8 its RELEASE gives, PROD_SUPP collapses to
# /gem_sw/prod//support, and gemUtil cannot find geminiRecords.dbd. Set it here
# rather than edit the vendored source, which stays as production built it.
export GEM_EPICS_RELEASE=R3.14.12.8

[ -d "$SUPPORT_SRC" ] || { echo "ERROR: $SUPPORT_SRC not found" >&2; exit 1; }

# Build order is DERIVED from each module's configure/RELEASE rather than
# hand-maintained: an earlier hand-written list missed that astlib needs
# slalib, because half the modules spell the variable PROD_SUPP and the other
# half PRODSUP. Any reference to $(VAR)/<mod>/<ver> counts as a
# dependency, whatever the variable is called. References to modules that are
# not vendored (pmaclib's stale gemUtil/1-13 line, which nothing uses) are
# ignored here; a real missing dependency still fails at compile time.
build_order() {
    local done="" left m deps d ok progress
    left=$(ls "$SUPPORT_SRC" | xargs)
    while [ -n "$left" ]; do
        progress=0
        for m in $left; do
            deps=$(grep -hvE '^[[:space:]]*#' "$SUPPORT_SRC"/$m/*/configure/RELEASE* 2>/dev/null \
                   | grep -oE '\)/[A-Za-z0-9_]+/[0-9]' | cut -d/ -f2 \
                   | sort -u | grep -vx "$m" || true)
            ok=1
            for d in $deps; do
                [ -d "$SUPPORT_SRC/$d" ] || continue          # not vendored: ignore
                echo " $done " | grep -q " $d " || { ok=0; break; }
            done
            if [ $ok = 1 ]; then
                done="$done $m"; left=$(echo $left | tr ' ' '\n' | grep -vx "$m" | xargs)
                progress=1
            fi
        done
        [ $progress = 1 ] || { echo "ERROR: dependency cycle among: $left" >&2; exit 1; }
    done
    echo $done
}
ORDER=$(build_order)

modver() {
    # modver <name> -> "<name>/<version>", failing loudly rather than silently
    # skipping a module the IOC will later fail to link against.
    local m="$1" v
    v=$(ls -1 "$SUPPORT_SRC/$m" 2>/dev/null | head -1)
    [ -n "$v" ] || { echo "ERROR: no version of '$m' under $SUPPORT_SRC" >&2; exit 1; }
    echo "$m/$v"
}

echo "=== staging vendored modules into $PRODSUP ==="
mkdir -p "$PRODSUP"
for m in $ORDER; do
    mv=$(modver "$m")
    mkdir -p "$PRODSUP/${mv%%/*}"
    # -n so a real NFS mount (a developer's workstation) is never shadowed.
    ln -sfn "$SUPPORT_SRC/$mv" "$PRODSUP/$mv"
    echo "  $PRODSUP/$mv -> $SUPPORT_SRC/$mv"
done

if [ "$STAGE_ONLY" = "1" ]; then
    echo
    echo "--stage-only: symlinks re-pointed at $SUPPORT_SRC; not building."
    exit 0
fi

echo
echo "=== building ==="
for m in $ORDER; do
    mv=$(modver "$m")
    echo
    echo "---- $mv ----"
    # Build through the symlink, so the module sees itself at the same path its
    # dependants will reference it by.
    make -C "$PRODSUP/$mv" -s
done

echo
echo "=== support modules built ==="
for m in $ORDER; do
    mv=$(modver "$m")
    n=$(ls "$SUPPORT_SRC/$mv/lib/RTEMS-mvme2307" 2>/dev/null | wc -l)
    printf "  %-24s %s RTEMS-mvme2307 libs\n" "$mv" "$n"
done
