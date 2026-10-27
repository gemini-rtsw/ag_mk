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

[ -d "$SUPPORT_SRC" ] || { echo "ERROR: $SUPPORT_SRC not found" >&2; exit 1; }

# Build order. The leaves have no inter-module dependencies; tcslib needs
# astlib/geminiRec/slalib/timelib, and agSeq needs tcslib on top of those.
# Derived from each module's configure/RELEASE -- see the dependency scan in
# PORTING.md. Anything not listed here is a leaf.
LEAVES="astlib geminiRec slalib timelib bancomm xycom pmaclib seq pvload iocStats timeProbe gemUtil"
ORDERED_TAIL="tcslib agSeq"

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
for m in $LEAVES $ORDERED_TAIL; do
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
for m in $LEAVES $ORDERED_TAIL; do
    mv=$(modver "$m")
    echo
    echo "---- $mv ----"
    # Build through the symlink, so the module sees itself at the same path its
    # dependants will reference it by.
    make -C "$PRODSUP/$mv" -s
done

echo
echo "=== support modules built ==="
for m in $LEAVES $ORDERED_TAIL; do
    mv=$(modver "$m")
    n=$(ls "$SUPPORT_SRC/$mv/lib/RTEMS-mvme2307" 2>/dev/null | wc -l)
    printf "  %-24s %s RTEMS-mvme2307 libs\n" "$mv" "$n"
done
