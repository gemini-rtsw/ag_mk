#!/bin/bash
#
# svn-to-git.sh -- convert the ag/mk SVN trunk to a git repo, with history.
#
# RUN THIS ON hbfrtdev-lv2 (or any host that can reach sbfsvn02).
# The build machine cannot: sbfsvn02 resolves to 172.16.5.83 but is not
# routable from outside the internal network.
#
#   ./svn-to-git.sh                  # writes ./ag_mk-git
#   ./svn-to-git.sh -o /var/tmp/x    # somewhere else
#
# Produces a normal git repo with full trunk history. Copy the whole directory
# out; it is self-contained (a few MB -- the source tree is only 178 files).

set -euo pipefail

SVN_URL="http://sbfsvn02/gemini-sw/gem/trunk/ioc/ag/mk"
OUT="./ag_mk-git"

while [ $# -gt 0 ]; do
    case "$1" in
        -o) [ -n "${2:-}" ] || { echo "ERROR: -o needs a value" >&2; exit 1; }
            OUT="$2"; shift 2 ;;
        -u) [ -n "${2:-}" ] || { echo "ERROR: -u needs a value" >&2; exit 1; }
            SVN_URL="$2"; shift 2 ;;
        -h|--help) sed -n '2,16p' "$0"; exit 0 ;;
        *) echo "unknown arg: $1" >&2; exit 1 ;;
    esac
done

command -v git >/dev/null || { echo "ERROR: git not found" >&2; exit 1; }
git svn --version >/dev/null 2>&1 || {
    echo "ERROR: 'git svn' is not available." >&2
    echo "       Install it:  sudo dnf install git-svn   (or git-core-doc/subversion-perl)" >&2
    echo "       If you cannot, run this instead and send me the dump file:" >&2
    echo "         svnrdump dump $SVN_URL > ag-mk-svn.dump" >&2
    exit 1; }

echo "source : $SVN_URL"
echo "output : $OUT"

# ---------------------------------------------------------------------------
# Authors map. Without it every commit is attributed to
# "hstecher <hstecher@303ae0b8-5cfe-405b-ba84-a597b98f2cc0>" -- the raw SVN
# username and the repository UUID -- which is unreadable in git log and
# impossible to map to a person later. Build it from the log up front.
# ---------------------------------------------------------------------------
AUTHORS="$(pwd)/ag-mk-authors.txt"
if [ ! -f "$AUTHORS" ]; then
    echo "building authors map -> $AUTHORS"
    svn log -q "$SVN_URL" 2>/dev/null \
      | awk -F'|' '/^r[0-9]+/ {gsub(/ /,"",$2); if ($2!="") print $2}' \
      | sort -u \
      | while read -r u; do
            # Best-effort guess at the real address; edit before rerunning if
            # any of these are wrong, and they are preserved in the git history
            # forever.
            echo "$u = $u <$u@noirlab.edu>"
        done > "$AUTHORS"
    echo "--- review this and fix any wrong addresses, then rerun ---"
    cat "$AUTHORS"
    echo "---------------------------------------------------------"
fi

# No -s/--stdlayout: the path is already the module root, and trunk/branches/
# tags do not exist beneath it (releases live under gem/release/support/...).
git svn clone "$SVN_URL" \
    --authors-file="$AUTHORS" \
    --no-metadata \
    "$OUT"

cd "$OUT"

# git svn leaves the checkout on a detached-ish master; make it main to match
# what the GitHub repo expects.
git branch -M main 2>/dev/null || true

echo
echo "=== history ==="
git log --oneline | head -20
echo "..."
echo "total commits: $(git rev-list --count HEAD)"
echo
echo "=== authors seen ==="
git log --format='%an <%ae>' | sort | uniq -c | sort -rn

cat <<NEXT

--------------------------------------------------------------------
Done: $OUT

Copy that whole directory out. Do NOT push it yet -- the .gitignore,
spec, CI workflow and vendored support modules still need to be added
on top, and it is easier to do that before the first push than after.
--------------------------------------------------------------------
NEXT
