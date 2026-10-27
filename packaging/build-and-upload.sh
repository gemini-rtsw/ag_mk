#!/bin/bash
#
# build-and-upload.sh -- build the two SHARED EPICS-3.14 RPMs and register them
# in the gemini-rtsw rpm-repo.
#
#   rtems410        the frozen RTEMS 4.10 cross-toolchain (repackaged)
#   epics-base-314  EPICS base R3.14.12.8, host + RTEMS-mvme2307/mvme3100
#
# These are shared: ag_mk and the second EPICS 3.14 repo both BuildRequire
# them, which is why they belong in rpm-repo rather than vendored per-repo.
# The small support modules go in each repo as source instead.
#
# Usage:
#   ./build-and-upload.sh --tarballs /path/to/ade-collect            # build only
#   ./build-and-upload.sh --tarballs /path/to/ade-collect --upload   # + register
#
# After --upload, finish in the browser:
#   Actions -> rebuild-latest -> Run workflow   (allow_shrink = false)
# That does the multi-GB :latest rebuild on a runner instead of this machine.

set -euo pipefail

TARBALLS=""
DO_UPLOAD=0
EL=9
ONLY=""

# `set -u` turns a flag given without its value into an unbound-variable crash
# with no useful message, so check for the value explicitly.
argval() {
    [ $# -ge 2 ] && [ -n "$2" ] || { echo "ERROR: $1 needs a value" >&2; exit 1; }
    echo "$2"
}

OUT=""
while [ $# -gt 0 ]; do
    case "$1" in
        --tarballs) TARBALLS=$(argval "$@"); shift 2 ;;
        --out)      OUT=$(argval "$@"); shift 2 ;;
        --el)       EL=$(argval "$@"); shift 2 ;;
        --only)     ONLY=$(argval "$@"); shift 2 ;;   # rtems410 | epics-base-314
        --upload)   DO_UPLOAD=1; shift ;;
        -h|--help)  sed -n '2,24p' "$0"; exit 0 ;;
        *) echo "unknown arg: $1" >&2; exit 1 ;;
    esac
done

[ -n "$TARBALLS" ] || { echo "ERROR: --tarballs <dir> is required" >&2; exit 1; }
[ -d "$TARBALLS" ] || { echo "ERROR: --tarballs '$TARBALLS' is not a directory" >&2; exit 1; }
TARBALLS=$(cd "$TARBALLS" && pwd)

HERE=$(cd "$(dirname "$0")" && pwd)

# The specs live beside this script. Copying build-and-upload.sh out on its own
# is the easy mistake, so say so rather than failing later on `cp: cannot stat`.
for spec in rtems410.spec epics-base-314.spec; do
    [ -f "$HERE/$spec" ] || {
        echo "ERROR: $HERE/$spec not found." >&2
        echo "       Copy the whole packaging/ directory, not just this script." >&2
        exit 1; }
done

# Default output next to the tarballs. Deriving it from the script location
# only works when the script sits inside the repo, which it may not.
[ -n "$OUT" ] || OUT="$TARBALLS/rpms"
mkdir -p "$OUT"
OUT=$(cd "$OUT" && pwd)
WORK="$OUT/.rpmbuild"

# Stamps the RPM Release. Taken from the repo this script lives in when there
# is one; "nogit" is fine for a hand-run build off a copied-out directory.
GIT_HASH=$(git -C "$HERE" rev-parse --short HEAD 2>/dev/null || true)
BUILDER="rockylinux:${EL}"

echo "tarballs : $TARBALLS"
echo "output   : $OUT"
echo "builder  : $BUILDER   (el${EL})"
echo "git hash : $GIT_HASH"

# Resolve a source tarball, accepting any of the names it may have been
# created under, and echo the one that exists.
pick() {
    for n in "$@"; do [ -f "$TARBALLS/$n" ] && { echo "$n"; return 0; }; done
    echo "ERROR: none of these found in $TARBALLS:" >&2
    for n in "$@"; do echo "         $n" >&2; done
    exit 1
}

# ---------------------------------------------------------------------------
# Build one spec inside a throwaway container.
#
# Everything runs in the container so the result does not depend on this
# machine having rpmbuild, a matching EL, or the right perl modules -- the same
# reason gemini-rtsw-ci builds in a container rather than on the runner.
# ---------------------------------------------------------------------------
build_spec() {
    local spec="$1"; shift
    local src="$1"; shift
    local extra_rpms="${1:-}"

    echo ""
    echo "=============================================================="
    echo "Building $spec"
    echo "=============================================================="

    rm -rf "$WORK"
    mkdir -p "$WORK"/{SPECS,SOURCES,RPMS,BUILD,BUILDROOT,SRPMS,PREINSTALL}
    cp "$HERE/$spec" "$WORK/SPECS/"
    cp "$TARBALLS/$src" "$WORK/SOURCES/"
    # The spec names one Source0; point it at the file we actually resolved so
    # the two cannot drift apart.
    sed -i -E "s|^(Source0:[[:space:]]*).*|\\1$src|" "$WORK/SPECS/$spec"
    # Locally built RPMs an earlier stage produced and this one BuildRequires
    # (epics-base-314 needs rtems410, which is not in rpm-repo on a first run).
    if [ -n "$extra_rpms" ]; then
        cp $extra_rpms "$WORK/PREINSTALL/" 2>/dev/null || true
    fi

    # rpmbuild runs as root inside the container, on bind-mounted host
    # directories. Without handing ownership back at the end, the next stage's
    # `rm -rf "$WORK"` fails with a screenful of "Permission denied" and the
    # build dies half way through.
    docker run --rm \
        -v "$WORK":/rpmbuild \
        -v "$OUT":/out \
        -e GIT_HASH="$GIT_HASH" \
        -e HOST_UID="$(id -u)" -e HOST_GID="$(id -g)" \
        "$BUILDER" bash -euo pipefail -c '
            dnf install -y --allowerasing rpm-build rpmdevtools dnf-plugins-core tar gzip findutils >/dev/null
            dnf install -y epel-release >/dev/null 2>&1 || true
            if [ -f /etc/yum.repos.d/rocky.repo ]; then
                dnf config-manager --set-enabled crb >/dev/null 2>&1 || \
                dnf config-manager --set-enabled powertools >/dev/null 2>&1 || true
            fi

            # Install locally-built prerequisites before resolving BuildRequires.
            if ls /rpmbuild/PREINSTALL/*.rpm >/dev/null 2>&1; then
                echo "-- installing locally built prerequisites --"
                dnf install -y /rpmbuild/PREINSTALL/*.rpm
            fi

            spec=$(ls /rpmbuild/SPECS/*.spec)
            echo "-- dnf builddep --"
            dnf builddep -y "$spec"

            echo "-- rpmbuild --"
            rpmbuild --define "_topdir /rpmbuild" -bb "$spec"

            cp -v /rpmbuild/RPMS/*/*.rpm /out/

            # Hand the bind mounts back to the invoking user (see above).
            chown -R "$HOST_UID:$HOST_GID" /rpmbuild /out
        '
}

# ---------------------------------------------------------------------------
# Stage 1 -- rtems410. No dependencies; pure repackage.
# ---------------------------------------------------------------------------
if [ -z "$ONLY" ] || [ "$ONLY" = "rtems410" ]; then
    src=$(pick rtems-4.10-gem.tar.gz rtems-4.10.tar.gz)
    build_spec rtems410.spec "$src"
fi

# ---------------------------------------------------------------------------
# Stage 2 -- epics-base-314. BuildRequires rtems410, so it is fed the RPM that
# stage 1 just produced rather than expecting it to already be published.
# ---------------------------------------------------------------------------
if [ -z "$ONLY" ] || [ "$ONLY" = "epics-base-314" ]; then
    # The PREBUILT tree is the one we want: there is no source tree anywhere
    # (MANIFEST section 2), and the prebuilt one already carries the
    # RTEMS-mvme2307/mvme3100 libraries. The -src tarball is configure/ and
    # templates only -- useless on its own.
    src=$(pick epics-base-R3.14.12.8-prebuilt.tar.gz epics-base-R3.14.12.8-gem.tar.gz)
    # No prerequisite RPM: rtems410 is a runtime Requires, not a BuildRequires,
    # so there is nothing to install to run this repackage.
    build_spec epics-base-314.spec "$src"
fi

echo ""
echo "=============================================================="
echo "Built RPMs"
echo "=============================================================="
ls -la "$OUT"/*.rpm

# ---------------------------------------------------------------------------
# Register in rpm-repo.
#
# --tag-only pushes each RPM as its own tiny FROM-scratch tag and STOPS. The
# alternative pulls every existing tag plus the multi-GB :latest to rebuild it
# here; the rebuild-latest Action does that on a runner instead.
# ---------------------------------------------------------------------------
if [ "$DO_UPLOAD" = "1" ]; then
    echo ""
    echo "=============================================================="
    echo "Registering in rpm-repo (scratch tags only)"
    echo "=============================================================="

    TOOLS="$OUT/.rpm-repo-tools"
    rm -rf "$TOOLS"
    git clone --depth 1 https://github.com/gemini-rtsw/gemini-rtsw-repo.git "$TOOLS"

    chmod +x "$TOOLS/upload-rpm.sh"
    ( cd "$TOOLS" && ./upload-rpm.sh --tag-only "$OUT"/*.rpm )

    cat <<'NEXT'

--------------------------------------------------------------------
Scratch tags pushed. One manual step left, in the browser:

  github.com/gemini-rtsw/gemini-rtsw-repo
    -> Actions -> rebuild-latest -> Run workflow
       allow_shrink = false        (we only ADDED packages)

That rebuilds ghcr.io/gemini-rtsw/rpm-repo:latest on a runner. Until it
finishes the RPMs are safe in their tags but not yet dnf-installable.
--------------------------------------------------------------------
NEXT
else
    echo ""
    echo "Not uploaded (--upload not given). To register:"
    echo "  $0 --tarballs $TARBALLS --upload"
fi
