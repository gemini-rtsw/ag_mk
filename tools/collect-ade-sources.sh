#!/bin/bash
#
# collect-ade-sources.sh -- gather everything needed to rebuild the EPICS
# 3.14.12.8 / RTEMS 4.10 world outside the Gemini internal network.
#
# RUN THIS ON hbfrtdev-lv2 (or any host with /gem_sw mounted).
#
# It is strictly READ-ONLY against /gem_sw. Everything it produces lands in
# one output directory that you then copy out.
#
#   ./collect-ade-sources.sh                 # writes to ./ade-collect
#   ./collect-ade-sources.sh -o /var/tmp/ade # somewhere with room
#   ./collect-ade-sources.sh -n              # probe + manifest only, no tars
#
# Paths are auto-discovered but can be forced:
#   RTEMS_DIR=... EPICS_BASE_DIR=... SUPPORT_DIR=... ./collect-ade-sources.sh
#
# Written for old bash (3.x) -- no mapfile, no associative arrays.

set -u

OUT="./ade-collect"
DRY=0
while [ $# -gt 0 ]; do
    case "$1" in
        -o) OUT="$2"; shift 2 ;;
        -n|--no-tar) DRY=1; shift ;;
        -h|--help) sed -n '2,20p' "$0"; exit 0 ;;
        *) echo "unknown arg: $1" >&2; exit 1 ;;
    esac
done

mkdir -p "$OUT" || { echo "cannot create $OUT" >&2; exit 1; }
OUT=$(cd "$OUT" && pwd)
MAN="$OUT/MANIFEST.txt"
: > "$MAN"

# Everything the script prints goes to the terminal AND into the manifest, so
# the file you send back is a complete record of what the machine reported.
say()  { echo "$*" | tee -a "$MAN"; }
head1() { say ""; say "================================================================"; say "$*"; say "================================================================"; }
# Run a command, showing it and its output, both to the terminal and the
# manifest. Never fails the script -- a missing optional tool must not stop the
# collection half way through.
cap() { say "\$ $*"; eval "$@" 2>&1 | sed 's/^/    /' | tee -a "$MAN"; }

say "ade collection -- $(date)"
say "host: $(hostname)  user: $(id -un)"
say "output: $OUT"

# ---------------------------------------------------------------------------
# 0. Locate the three trees
# ---------------------------------------------------------------------------
head1 "0. Locating source trees"

find_first() {
    # find_first <candidate> <candidate> ...  -> echoes the first that exists
    for c in "$@"; do [ -d "$c" ] && { echo "$c"; return 0; }; done
    return 1
}

RTEMS_DIR="${RTEMS_DIR:-$(find_first \
    /gem_sw/targetOS/RTEMS/rtems-4.10 \
    /gem_base/targetOS/RTEMS/rtems-4.10 \
    /gem_sw/targetOS/RTEMS/rtems/4.10 \
    /gemsoft/targetOS/RTEMS/rtems-4.10)}"

EPICS_BASE_DIR="${EPICS_BASE_DIR:-$(find_first \
    /gem_sw/epics/R3.14.12.8/base \
    /gem_base/epics/R3.14.12.8/base \
    /gemsoft/epics/R3.14.12.8/base)}"

SUPPORT_DIR="${SUPPORT_DIR:-$(find_first \
    /gem_sw/prod/R3.14.12.8/support \
    /gem_base/prod/R3.14.12.8/support)}"

say "RTEMS_DIR      = ${RTEMS_DIR:-<NOT FOUND>}"
say "EPICS_BASE_DIR = ${EPICS_BASE_DIR:-<NOT FOUND>}"
say "SUPPORT_DIR    = ${SUPPORT_DIR:-<NOT FOUND>}"

if [ -z "${RTEMS_DIR:-}" ] || [ -z "${EPICS_BASE_DIR:-}" ] || [ -z "${SUPPORT_DIR:-}" ]; then
    say ""
    say "!! One or more trees were not found. Re-run with them set explicitly, e.g.:"
    say "!!   RTEMS_DIR=/path/to/rtems-4.10 EPICS_BASE_DIR=/path/to/base \\"
    say "!!   SUPPORT_DIR=/path/to/support $0"
    say "!! Continuing with whatever was found."
fi

# ---------------------------------------------------------------------------
# 1. Probe the RTEMS 4.10 toolchain
#
#    This is the part I most need answered before designing the RPM: these are
#    x86_64 host binaries built around 2012. If they need a glibc older than
#    Rocky 8 ships, the build container has to be an older base image.
# ---------------------------------------------------------------------------
head1 "1. RTEMS 4.10 toolchain probe"

if [ -n "${RTEMS_DIR:-}" ]; then
    say "tree: $RTEMS_DIR"
    cap "du -sh '$RTEMS_DIR' 2>/dev/null"
    say ""
    say "-- top level --"
    cap "ls -la '$RTEMS_DIR'"

    # The cross-gcc may be at bin/ or one level down depending on how RSB laid
    # it out; look for it rather than assuming.
    GCC=$(find "$RTEMS_DIR" -maxdepth 4 -name 'powerpc-rtems4.10-gcc' -type f 2>/dev/null | head -1)
    [ -z "$GCC" ] && GCC=$(find "$RTEMS_DIR" -maxdepth 4 -name 'powerpc-rtems*-gcc*' 2>/dev/null | head -1)
    say ""
    say "-- cross compiler --"
    say "found: ${GCC:-<none>}"
    if [ -n "$GCC" ]; then
        cap "file '$GCC'"
        cap "ldd '$GCC'"
        cap "'$GCC' --version"
        cap "'$GCC' -print-search-dirs 2>&1 | head -5"
        # Exact glibc/libstdc++ symbol versions decide the builder base image.
        say ""
        say "-- glibc/libstdc++ versions the toolchain binaries require --"
        cap "find '$RTEMS_DIR' -maxdepth 4 -type f -perm -u+x -exec sh -c 'objdump -T \"\$1\" 2>/dev/null | grep -oE \"GLIBC(XX)?_[0-9.]+\"' _ {} \; 2>/dev/null | sort -u -V | tail -20"
    fi

    say ""
    say "-- BSPs present (need mvme2307 and mvme3100) --"
    cap "ls -d '$RTEMS_DIR'/powerpc-rtems4.10/*/ 2>/dev/null"
    for bsp in mvme2307 mvme3100; do
        if [ -d "$RTEMS_DIR/powerpc-rtems4.10/$bsp" ]; then
            say "    OK   $bsp present"
        else
            say "    MISS $bsp NOT FOUND -- the IOC targets this, flag it"
        fi
    done

    say ""
    say "-- anything outside the tree it may reference (symlinks pointing away) --"
    cap "find '$RTEMS_DIR' -type l -maxdepth 5 -exec readlink -f {} \; 2>/dev/null | grep -v \"^$RTEMS_DIR\" | sort -u | head -20"
else
    say "SKIPPED -- RTEMS_DIR not found"
fi

# ---------------------------------------------------------------------------
# 2. Probe EPICS base R3.14.12.8
#
#    Two things matter: (a) is the SOURCE here, so it can be rebuilt with the
#    right FINAL_LOCATION, and (b) which target architectures were built --
#    specifically whether RTEMS-mvme2307 exists, since stock 3.14.12 has no
#    such target and the shared epics-base-3.14.12 RPM has host libs only.
# ---------------------------------------------------------------------------
head1 "2. EPICS base R3.14.12.8 probe"

if [ -n "${EPICS_BASE_DIR:-}" ]; then
    say "tree: $EPICS_BASE_DIR"
    cap "du -sh '$EPICS_BASE_DIR' 2>/dev/null"
    cap "ls -la '$EPICS_BASE_DIR'"

    say ""
    say "-- is the source tree here? (need src/ + configure/ to rebuild) --"
    for d in src configure config startup documentation; do
        [ -d "$EPICS_BASE_DIR/$d" ] && say "    OK   $d/" || say "    --   $d/ absent"
    done

    say ""
    say "-- built target architectures --"
    cap "ls -d '$EPICS_BASE_DIR'/lib/*/ 2>/dev/null"
    cap "ls -d '$EPICS_BASE_DIR'/bin/*/ 2>/dev/null"

    say ""
    say "-- RTEMS target definitions (mvme2307 is a Gemini addition, not stock) --"
    cap "ls '$EPICS_BASE_DIR'/configure/os/ 2>/dev/null | grep -i rtems"

    say ""
    say "-- exact version --"
    cap "grep -hE '^(EPICS_VERSION|EPICS_REVISION|EPICS_MODIFICATION|EPICS_PATCH_LEVEL|EPICS_SITE_VERSION)' '$EPICS_BASE_DIR'/configure/CONFIG_BASE_VERSION 2>/dev/null"

    say ""
    say "-- RTEMS_BASE / RTEMS_VERSION as configured --"
    cap "grep -rhE '^[[:space:]]*(RTEMS_BASE|RTEMS_VERSION|RTEMS_TOOLS)[[:space:]]*=' '$EPICS_BASE_DIR'/configure/ 2>/dev/null | sort -u"

    say ""
    say "-- is it under version control? (an SVN URL beats a tarball) --"
    cap "svn info '$EPICS_BASE_DIR' 2>&1 | head -6"

    say ""
    say "-- Gemini build-rule files, if base carries its own copies --"
    cap "ls -la '$EPICS_BASE_DIR'/configure/CONFIG.Gem '$EPICS_BASE_DIR'/configure/RULES.Gem '$EPICS_BASE_DIR'/bin/linux-x86_64/convertGemRelease.pl 2>&1"
else
    say "SKIPPED -- EPICS_BASE_DIR not found"
fi

# ---------------------------------------------------------------------------
# 3. Support modules -- the 13 pinned in configure/RELEASE
# ---------------------------------------------------------------------------
head1 "3. Support modules"

# module:version, exactly as pinned in ag/mk configure/RELEASE
MODULES="
geminiRec:4-1-11
slalib:1-9-10
timelib:2-0-8
tcslib:1-0-16
bancomm:1-6-10
xycom:2-1-8
pmaclib:1-1-12
seq:2-2-5-3
pvload:1-1-4
iocStats:3-1-16-5
timeProbe:1-1-15
agSeq:3-2
gemUtil:1-14
"

MOD_PATHS=""
if [ -n "${SUPPORT_DIR:-}" ]; then
    for mv in $MODULES; do
        m=${mv%%:*}; v=${mv##*:}
        p="$SUPPORT_DIR/$m/$v"
        if [ -d "$p" ]; then
            sz=$(du -sh "$p" 2>/dev/null | awk '{print $1}')
            say "    OK   $m/$v   ($sz)"
            MOD_PATHS="$MOD_PATHS $m/$v"
        else
            say "    MISS $m/$v  -- NOT FOUND under $SUPPORT_DIR"
            say "         versions actually present: $(ls "$SUPPORT_DIR/$m" 2>/dev/null | tr '\n' ' ')"
        fi
    done

    say ""
    say "-- are these in SVN? (if so send URLs, not tarballs -- history survives) --"
    for mv in $MODULES; do
        m=${mv%%:*}; v=${mv##*:}
        [ -d "$SUPPORT_DIR/$m/$v" ] || continue
        u=$(svn info "$SUPPORT_DIR/$m/$v" 2>/dev/null | sed -n 's/^URL: //p')
        say "    $m/$v -> ${u:-<not an svn working copy>}"
    done
else
    say "SKIPPED -- SUPPORT_DIR not found"
fi

# ---------------------------------------------------------------------------
# 4. The two unresolved libraries
#
#    ag-mk-iocApp/src/Makefile links -llistAlarmRecords and -lnetConfig but
#    configure/RELEASE defines no variable for either, so I cannot tell which
#    module ships them.
# ---------------------------------------------------------------------------
head1 "4. Hunting listAlarmRecords and netConfig"

if [ -n "${SUPPORT_DIR:-}" ]; then
    for lib in listAlarmRecords netConfig; do
        say ""
        say "-- $lib --"
        cap "find '$SUPPORT_DIR' -maxdepth 5 \( -name 'lib${lib}.*' -o -name '${lib}.dbd' \) 2>/dev/null | head -10"
    done
    say ""
    say "-- fallback: grep the whole support tree --"
    cap "grep -rl 'listAlarmRecords\|netConfig' '$SUPPORT_DIR'/*/*/dbd '$SUPPORT_DIR'/*/*/src 2>/dev/null | head -10"
fi

# ---------------------------------------------------------------------------
# 5. Reference build -- the known-good db/ from production
#
#    Not needed to build, but it is the only way to prove the .db files TDCT
#    generates in CI match what is actually running on the telescope.
# ---------------------------------------------------------------------------
head1 "5. Production reference build of ag/mk"

PRODIOC=$(find_first \
    /gem_sw/prod/R3.14.12.8/ioc/ag/mk \
    /gem_base/prod/R3.14.12.8/ioc/ag/mk)
if [ -n "${PRODIOC:-}" ]; then
    say "tree: $PRODIOC"
    cap "ls -la '$PRODIOC'"
    NEWEST=$(ls -1d "$PRODIOC"/*/ 2>/dev/null | sort -V | tail -1)
    say "newest release dir: ${NEWEST:-<none>}"
    if [ -n "${NEWEST:-}" ]; then
        cap "ls -la '${NEWEST}db' 2>/dev/null | head -20"
    fi
else
    say "not found -- adjust by hand if the prod IOC tree lives elsewhere"
fi

# ---------------------------------------------------------------------------
# 6. TDCT -- the build runs it to turn .sch into .db
# ---------------------------------------------------------------------------
head1 "6. TDCT"

cap "echo \"TDCT env var: '\${TDCT:-<unset>}'\""
cap "echo \"EPICS env var: '\${EPICS:-<unset>}'\""
TDCTJAR=$(find_first "${TDCT:-/nonexistent}" /gem_sw/epics/extensions/src/tdct /gem_base/epics/extensions/src/tdct)
say "tdct dir: ${TDCTJAR:-<not found>}"
[ -n "${TDCTJAR:-}" ] && cap "ls -la '$TDCTJAR'/*.jar '$TDCTJAR'/sym 2>/dev/null | head -20"
cap "java -version 2>&1 | head -3"

# ---------------------------------------------------------------------------
# 7. Tarballs
# ---------------------------------------------------------------------------
head1 "7. Creating tarballs"

if [ "$DRY" = "1" ]; then
    say "-n given -- skipping tar creation. Send $MAN on its own."
else
    # pigz if available: these trees are large and gzip is single-threaded.
    if command -v pigz >/dev/null 2>&1; then ZIP="pigz"; else ZIP="gzip"; fi
    say "compressor: $ZIP"

    tarball() {
        # tarball <name> <parent-dir> <relative-path...>
        name="$1"; parent="$2"; shift 2
        out="$OUT/$name.tar.gz"
        say ""
        say "-> $name.tar.gz  (from $parent: $*)"
        # --ignore-failed-read so one unreadable file does not lose the whole
        # archive; the exit status is reported either way.
        tar -C "$parent" --ignore-failed-read -cf - "$@" 2>>"$MAN" | $ZIP > "$out"
        rc=$?
        if [ -s "$out" ]; then
            say "   $(du -sh "$out" | awk '{print $1}')  rc=$rc"
        else
            say "   FAILED (empty) rc=$rc"
        fi
    }

    # 7a. RTEMS 4.10 toolchain -- binary, repackaged as-is into an RPM.
    if [ -n "${RTEMS_DIR:-}" ]; then
        tarball "rtems-4.10-gem" "$(dirname "$RTEMS_DIR")" "$(basename "$RTEMS_DIR")"
    fi

    # 7b. EPICS base -- SOURCE, so it can be rebuilt with the correct
    #     FINAL_LOCATION rather than carrying baked-in /gem_sw paths.
    if [ -n "${EPICS_BASE_DIR:-}" ]; then
        tarball "epics-base-R3.14.12.8-src" "$(dirname "$EPICS_BASE_DIR")" \
            --exclude='lib' --exclude='bin' --exclude='include' \
            --exclude='O.*' --exclude='.svn' \
            "$(basename "$EPICS_BASE_DIR")"

        # 7c. ...and the PREBUILT tree separately. This is the fallback if the
        #     source rebuild against RTEMS 4.10 proves too painful, and the
        #     reference to diff a fresh build against.
        tarball "epics-base-R3.14.12.8-prebuilt" "$(dirname "$EPICS_BASE_DIR")" \
            --exclude='.svn' "$(basename "$EPICS_BASE_DIR")"
    fi

    # 7d. Support modules -- source only. These get vendored into each repo,
    #     so strip build products to keep them small.
    if [ -n "${SUPPORT_DIR:-}" ] && [ -n "$MOD_PATHS" ]; then
        tarball "ag-mk-support-3.14-src" "$SUPPORT_DIR" \
            --exclude='O.*' --exclude='.svn' --exclude='*.o' --exclude='*.a' \
            --exclude='lib' --exclude='bin' \
            $MOD_PATHS
    fi

    # 7e. Prebuilt support libraries, kept apart. Small, and the only way to
    #     confirm a rebuilt module produces the same objects as production.
    if [ -n "${SUPPORT_DIR:-}" ] && [ -n "$MOD_PATHS" ]; then
        tarball "ag-mk-support-3.14-prebuilt-libs" "$SUPPORT_DIR" \
            --exclude='.svn' $MOD_PATHS
    fi

    # 7f. Production db/ reference.
    if [ -n "${NEWEST:-}" ] && [ -d "${NEWEST}db" ]; then
        tarball "ag-mk-prod-db-reference" "$NEWEST" "db"
    fi

    say ""
    say "-- checksums --"
    ( cd "$OUT" && md5sum ./*.tar.gz 2>/dev/null ) | tee -a "$MAN"
fi

head1 "Done"
say "Everything is in: $OUT"
cap "ls -la '$OUT'"
cap "du -sh '$OUT'"
say ""
say "Copy that directory over. MANIFEST.txt is the important part -- send it"
say "even if some tarballs are too large to move in one go."
