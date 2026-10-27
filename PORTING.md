# Porting ag/mk to the gemini-rtsw GitHub pipeline

Status: **shared RPMs built, verified and published.** The IOC itself is not
built yet. See [Still open](#still-open).

## Published to rpm-repo (2026-08-28)

| RPM | size | contents |
|---|---|---|
| `rtems410-4.10-0.gem20190703.el9.noarch` | 121 MB | gcc 4.4.7 / Newlib 1.18.0 cross-toolchain, BSPs mvme2307/3100/5500/beatnik |
| `epics-base-314-3.14.12.8-0.gem20190703.el9.noarch` | 37 MB | base runtime, host + 4 RTEMS targets, 15 libs each |
| `epics-base-314-devel-…` | 1 MB | headers, `configure/`, templates |

Scratch tags are pushed and confirmed present in GHCR. They become
`dnf`-installable once **Actions -> rebuild-latest** has run on
`gemini-rtsw/gemini-rtsw-repo`.

Verified in a clean `rockylinux:9` container: all three install, and a source
including `epicsTime.h` cross-compiles for mvme2307 against the shipped base,
with `epicsTimeGetCurrent` resolving in `libCom.a`.

### What the collected tree actually showed

Three findings changed the design from the original plan:

1. **There is no EPICS source tree** on `/gem_sw` — only the installed product.
   But it already carries `lib/RTEMS-mvme2307` and `lib/RTEMS-mvme3100`, so
   there is nothing to compile and nothing to gain by trying. Both packages are
   **repackages**, not builds.
2. **The 2012 toolchain runs on Rocky 9 unmodified** — the highest symbol
   version required anywhere in the tree is `GLIBC_2.14` (Rocky 9 ships 2.34),
   and it relocates correctly, since gcc resolves its search dirs from
   `argv[0]`. Tested by unpacking elsewhere and cross-compiling. No old base
   image is needed.
3. **`listAlarmRecords` and `netConfig` both come from `gemUtil/1-14`**, which
   was already in `configure/RELEASE`. Nothing was missing after all.

### Why both install at the original `/gem_sw` paths

Relocation works, so this is a choice rather than a constraint. EPICS base hard
codes `RTEMS_BASE = /gem_sw/targetOS/RTEMS/rtems-$(RTEMS_VERSION)`, and every
IOC's `configure/RELEASE` points into `/gem_sw`. Installing where the files
already expect to be means **the IOC sources need no edits at all** to build in
CI, and a developer's NFS-mounted workstation behaves identically to the
container.

### Two judgement calls worth knowing

- **`AutoReqProv: no`** on both, as `scs_mk.spec` already does. RPM scanned the
  2019 binaries and demanded `libncurses.so.5`, `libtinfo.so.5`,
  `libpython2.7.so.1.0`, `libreadline.so.6` and `/usr/local/bin/perl` — none
  installable on Rocky 9. They are needed only by `powerpc-rtems4.10-gdb` and
  the host `softIoc`. **Consequence: gdb will not run on Rocky 9 without
  ncurses-compat and python2.** Cross-compiling is unaffected.
- **Release is `0.gem20190703`**, naming the source snapshot. `ag_mk` is not a
  git repo yet, and scratch tags are keyed on the full NVRA and never
  overwrite — so `nogit` would have been a bad permanent name.

## What this package is

`ag/mk` is the Gemini North Acquisition & Guidance IOC. It is currently an
**SVN working copy**, not git:

| | |
|---|---|
| SVN URL | `http://sbfsvn02/gemini-sw/gem/trunk/ioc/ag/mk` |
| Revision in this tree | r6918 |
| Tracked files | 178 nodes under `ag-mk-iocApp/`, `configure/`, `iocBoot/`, plus 4 top-level files |
| Untracked in this tree | `simTCS/` (35 MB of prebuilt softIoc), `lib/`, `dbd/`, `O.*` — all build output or scratch |

The source itself is small. Everything else on disk is build product.

## Why it cannot just use the standard pipeline

The pipeline builds against **EPICS 7.0.7 + RTEMS 6.2**. This IOC is
**EPICS 3.14.12.8 + RTEMS 4.10**. Those are not two versions of one thing —
they are different compilers, different C libraries, and a different EPICS API.

Verified from the committed object files
(`ag-mk-iocApp/src/O.RTEMS-mvme2307/*.o`, `.comment` section):

```
GCC: (GNU) 4.4.7 20120313 (RTEMS 4.10, RSB ad29cd659d886c448e0b8ed240f833f4cf437478, Newlib 1.18.0)
```

| | this IOC needs | pipeline has today |
|---|---|---|
| EPICS base | 3.14.12.8 (Gemini-patched) | 7.0.7 |
| RTEMS | **4.10** | 6.2 |
| Cross gcc | 4.4.7 / Newlib 1.18.0 | RTEMS 6 toolchain |
| Toolchain path | `/gem_sw/targetOS/RTEMS/rtems-4.10` | `/gem_base/targetOS/RTEMS/rtems/6` |
| Targets | `RTEMS-mvme2307`, `RTEMS-mvme3100` | `powerpc-net-legacy` BSPs |
| Support module paths | `/gem_sw/prod/R3.14.12.8/support/<mod>/<ver>` | `/gem_base/epics/support/<mod>` |

### What the shared rpm-repo already has (checked: 1026 RPMs)

Good news, partially:

- `epics-base-3.14.12-10.el9.gemini.x86_64` **exists** — but it ships
  `lib/linux-x86_64` only. **No RTEMS cross-build**, and its
  `configure/os/` has no `CONFIG.Common.RTEMS-mvme2307` at all
  (stock 3.14.12 ships mvme2100/2700/3100/5500 — 2307 is a Gemini addition).
  So it is not usable as-is for this IOC.
- `gemini-ade` **is reusable and version-neutral** — it provides `CONFIG.Gem`,
  `RULES.Gem`, and `convertGemRelease.pl`, all of which this build needs, and it
  does *not* drag in EPICS 7 or RTEMS 6.
- `tdct-2.18.6-5.el9` exists — needed, see below.
- Every support module is present **but only at EPICS-7 versions**
  (`geminiRec-4.1.13`, `slalib-1.9.7`, `timelib-2.1.4`, `tcslib-1.1.1`,
  `bancomm-1.6.13`, `xycom-2.1.12`, `pmaclib-1.1.12`, `pvload-1.2.1`,
  `gemUtil-1.6.13`, `timeProbe-1.1.16`, `sequencer-2.2.9`). None match the
  3.14 pins below, and none are RTEMS-4.10 objects.
- **Absent entirely:** any RTEMS 4.10, `iocStats`, `agSeq`,
  `listAlarmRecords`, `netConfig`.

### The build also runs TDCT

`ag-mk-iocApp/Db/` holds `.sch` schematics, not `.db` files — `db/` is a build
product. `RULES.Gem` turns one into the other by running a **Java GUI tool**:

```make
%.db: ../%.sch $(DEPSCHS)
	java -jar $(TDCT)/tdct.jar -ignoreversion -cfg $(TDCT_CFG) -st $< -db $(COMMON_DIR)
```

So the builder image needs `tdct`, a JRE, and (per `tdct.cfg`) the
`$(EPICS)/extensions/src/tdct/sym/` symbol library, with `SYS_TDCT_PATHS`
covering the 3.14 support modules' symbol dirs. `-ignoreversion` is already
passed, which is what makes a newer TDCT against older schematics plausible —
but it is unproven for these files and is a real risk to schedule.

## Dependencies to encapsulate

From `configure/RELEASE`, pinned versions, all under
`/gem_sw/prod/R3.14.12.8/support/`:

| module | version | linked as | confirmed used |
|---|---|---|---|
| geminiRec | 4-1-11 | `geminiRecords` | yes (headers in `.d` files) |
| slalib | 1-9-10 | `slalib` | yes |
| timelib | 2-0-8 | `timelib` | yes |
| tcslib | 1-0-16 | `tcslib` | yes |
| bancomm | 1-6-10 | `bancomm` | yes |
| xycom | 2-1-8 | `xy240` | yes (dbd) |
| pmaclib | 1-1-12 | `pmaclib` | yes |
| seq | 2-2-5-3 | `seq`, `pv` | yes |
| pvload | 1-1-4 | `pvload` | yes |
| iocStats | 3-1-16-5 | `devIocStats` | yes |
| timeProbe | 1-1-15 | `timeProbe` | yes |
| agSeq | 3-2 | `agSeq` | yes |
| gemUtil | 1-14 | (via RELEASE) | indirect |

Two libraries are linked in `ag-mk-iocApp/src/Makefile` with **no matching
`RELEASE` variable**, so I cannot tell which module ships them:

- `listAlarmRecords` (also `listAlarmRecords.dbd`)
- `netConfig` (note: `net_config.c`/`net_config.dbd` are local, the *library* is not)

`oiwfsgw` is referenced but commented out; ignoring it unless told otherwise.

## Agreed shape

Split by **size and sharing**, not by convenience:

| what | where | why |
|---|---|---|
| RTEMS 4.10 toolchain | **RPM** `rtems410` in rpm-repo | large, frozen, shared by both EPICS 3.14 repos |
| EPICS base 3.14.12.8 | **RPM** `epics-base-314` in rpm-repo | large, shared by both repos |
| The 13 support modules | **source, vendored in each repo** | small; per-repo copies avoid a versioning problem for two consumers |

Both RPMs are deliberately named apart from the existing packages
(`rtems` is 6.2, `epics-base` is 7.0.7 and a host-only 3.14.12). A build host
must be able to hold the EPICS 7 and EPICS 3.14 worlds at once.

Install prefixes follow the pipeline convention:

```
/gem_base/targetOS/RTEMS/rtems/4.10        rtems410       (cf. .../rtems/6)
/gem_base/epics/epics-base-3.14.12.8       epics-base-314
```

`epics-base-314` is **built from source**, not repackaged: a prebuilt EPICS tree
carries absolute `/gem_sw` paths through `configure/` and `envPaths`, and
rebuilding with `FINAL_LOCATION` set is what makes it relocatable. `rtems410`
*is* a straight repackage — gcc 4.4.7 will not rebuild under a modern host
compiler, and the toolchain is frozen anyway.

### One caveat worth knowing before we push

Every `epics` -profile build in the org pulls `rpm-repo:latest` in full, and the
readme already warns the served image "eventually strains runner disk" —
`gemini-rtsw-ci/ci.yml` has a *Free up disk space* step reclaiming 30-40 GB just
to make room. The RTEMS 4.10 toolchain is likely 0.5-1.5 GB.

Adding it makes **every** repo's build a little slower, not just the 3.14 ones.
That is the price of the RPMs being shared, and it is a fair trade — but if
builds start timing out, the fix is to prune stale scratch tags
(`repo-usage.sh`, then `prune-pkg.sh`), not to unpick this.

## Files added so far

| file | what it does |
|---|---|
| `tools/collect-ade-sources.sh` | **Run on hbfrtdev-lv2.** Read-only. Probes the three trees, writes `MANIFEST.txt` plus the tarballs. |
| `packaging/rtems410.spec` | Repackages the toolchain. Draft — verify against MANIFEST. |
| `packaging/epics-base-314.spec` | Builds base for host + mvme2307 + mvme3100. Draft — verify against MANIFEST. |
| `packaging/build-and-upload.sh` | Builds both RPMs in a container, then registers them with `upload-rpm.sh --tag-only`. |
| `.gitignore` | Build products. Note `configure/CONFIG_SITE.local` stays tracked — it carries `-DGEMINI_NORTH`. |

Both specs are marked DRAFT because two things can only be settled by looking at
what the collection script reports: whether the EPICS tree really carries its
source, and how `RTEMS_BASE` / `RTEMS_VERSION` are spelled in 3.14's
`configure/os/CONFIG_SITE.Common.RTEMS`. Send `MANIFEST.txt` and I will finish
them.

## How to run it

On **hbfrtdev-lv2**:

```bash
# copy tools/collect-ade-sources.sh over, then:
./collect-ade-sources.sh -o /var/tmp/ade-collect

# probe first if you want to see what it finds before it tars anything:
./collect-ade-sources.sh -n -o /var/tmp/ade-collect
```

Paths are auto-discovered; force them if the guesses are wrong:

```bash
RTEMS_DIR=/gem_sw/targetOS/RTEMS/rtems-4.10 \
EPICS_BASE_DIR=/gem_sw/epics/R3.14.12.8/base \
SUPPORT_DIR=/gem_sw/prod/R3.14.12.8/support \
./collect-ade-sources.sh -o /var/tmp/ade-collect
```

Then copy `/var/tmp/ade-collect` here. **Send `MANIFEST.txt` first, on its own** —
it is small, and it is what unblocks finishing the specs. The tarballs can
follow.

Once they land:

```bash
./packaging/build-and-upload.sh --tarballs /path/to/ade-collect
./packaging/build-and-upload.sh --tarballs /path/to/ade-collect --upload
```

then **Actions -> rebuild-latest -> Run workflow** on `gemini-rtsw-repo`, with
`allow_shrink = false` since we are only adding.

## Still open

These do not block collection — answer whenever.

1. **SVN history: keep or start clean?** Keeping it means `git svn clone` of
   `http://sbfsvn02/gemini-sw/gem/trunk/ioc/ag/mk`, which I cannot reach from
   here — you would run it, or send an `svnrdump`. Starting clean at r6918 is
   one commit and available now.
2. **Is `agSeq` the second 3.14 repo?** It is a separate SVN checkout
   (`~/work/agSeq`, R3.14.12.8) *and* a build dependency of this IOC. It can be
   its own repo or vendored here, not cleanly both. The collection script tars
   it either way.
3. **EL8, EL9, or both?** The scripts default to el9. Building both doubles the
   rpm-repo footprint of two large packages.
4. **`listAlarmRecords` and `netConfig`** — linked in `src/Makefile` with no
   `RELEASE` variable. Section 4 of the script hunts for them; if you know the
   module offhand it saves a round trip.
5. **Does TDCT 2.18.6 read these 3.14-era schematics?** Section 6 collects the
   version. The real test is opening one, and it is the biggest remaining
   unknown after the toolchain — `db/` is generated, so if TDCT cannot read
   `ag_top.sch` there is no build.
6. **GHCR access** — `gemini-rtsw/ag_mk` needs Write on the `rpm-repo` package
   (*Manage Actions access -> Add Repository*).
