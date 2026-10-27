# rtems410.spec -- Gemini RTEMS 4.10 PowerPC cross-toolchain + BSPs
#
# A REPACKAGE, not a build. The toolchain is gcc 4.4.7 / Newlib 1.18.0 from
# 2012 (RSB ad29cd659d886c448e0b8ed240f833f4cf437478). Rebuilding it from the
# RTEMS Source Builder on a modern host is not realistic, and it is frozen
# anyway, so we ship the binaries as they are.
#
# Verified against the collected tree (packaging/ade-collect/MANIFEST.txt):
#   - runs unmodified on Rocky 9: needs only libc.so.6 + ld-linux, and the
#     highest symbol version required anywhere in the tree is GLIBC_2.14
#     (Rocky 8 ships 2.28, Rocky 9 ships 2.34)
#   - relocatable: gcc resolves its search dirs relative to argv[0], so moving
#     the tree works. Tested by unpacking elsewhere and cross-compiling.
#   - produces "ELF 32-bit MSB relocatable, PowerPC" -- byte-format identical
#     to the objects committed in ag-mk-iocApp/src/O.RTEMS-mvme2307/
#
# INSTALL PATH: the original /gem_sw/targetOS/RTEMS/rtems-4.10.
# The toolchain relocates fine, so this is a choice, not a constraint. It is
# made because EPICS base 3.14's configure/os/CONFIG_SITE.Common.RTEMS hard
# codes
#     RTEMS_BASE = /gem_sw/targetOS/RTEMS/rtems-$(RTEMS_VERSION)
# and every IOC's configure/RELEASE points into /gem_sw. Installing where the
# files already expect to be means the IOC sources need no edits at all to
# build in CI, and a developer's NFS-mounted workstation behaves identically to
# the container.
#
# Named "rtems410", NOT "rtems": the pipeline already has rtems-6.2 under
# /gem_base/targetOS/RTEMS/rtems/6, and a build host must be able to hold the
# EPICS 7 and EPICS 3.14 worlds at the same time. Different name, different
# path, no file conflicts.

%global _enable_debug_package 0
%global debug_package %{nil}
# Prebuilt cross binaries: skip the post-install processing that assumes native
# ELF, which would strip or mangle them.
%global __os_install_post %{nil}
%global _missing_build_ids_terminate_build 0
# noarch by convention (a self-contained tree) though it holds x86_64 host
# binaries -- the same exception rtems.spec takes for RTEMS 6.
%global _binaries_in_noarch_packages_terminate_build 0

%define rtems_ver     4.10
%define rtems_prefix  /gem_sw/targetOS/RTEMS/rtems-%{rtems_ver}
# Provenance stamp. $GIT_HASH first (build_rpm.sh / build-and-upload.sh export
# it), then git, then a fixed fallback naming the source tree this was
# repackaged from -- the /gem_sw snapshot dated 2019-07-03. The generic "nogit"
# would be a poor permanent name: rpm-repo scratch tags are keyed on the full
# NVRA and never overwrite, so whatever Release ships here is forever.
%define git_hash %(if [ -n "$GIT_HASH" ]; then echo "$GIT_HASH"; else git rev-parse --short HEAD 2>/dev/null || echo gem20190703; fi)

Name:           rtems410
Version:        4.10
Release:        0.%{git_hash}%{?dist}
Summary:        RTEMS 4.10 PowerPC cross-toolchain and BSPs (mvme2307, mvme3100)
License:        GPLv2 and GPLv3 and BSD-2-Clause
URL:            https://www.rtems.org/
Source0:        rtems-4.10-gem.tar.gz
BuildArch:      noarch

BuildRequires:  tar gzip findutils coreutils

# The tree is a 2019 snapshot built on an older EL, and rpm's automatic
# dependency generator scans every host binary in it. Doing so pulls in
# libncurses.so.5, libtinfo.so.5 and libpython2.7.so.1.0 -- needed only by
# powerpc-rtems4.10-gdb, and unsatisfiable on Rocky 9. The compiler itself
# needs nothing but libc (verified: GLIBC_2.14 is the highest version required
# anywhere in the tree), so deriving deps from these binaries produces garbage
# that blocks installation for no benefit. Same call scs_mk.spec makes.
#
# Consequence, stated plainly: powerpc-rtems4.10-gdb will not run on Rocky 9
# without ncurses-compat/python2 present. Cross-compiling, which is what CI
# needs, is unaffected.
AutoReqProv:    no

%description
RTEMS 4.10 PowerPC cross development tools (gcc 4.4.7, Newlib 1.18.0) and the
Gemini board support packages, installed under %{rtems_prefix}.

BSPs: mvme2307, mvme3100, mvme5500, beatnik.

Consumed by epics-base-314 and by the EPICS 3.14 IOCs that cross-compile
against it. Kept separate from the "rtems" package (RTEMS 6.2) so both
toolchains can be installed side by side.

%prep
%setup -q -n rtems-4.10

%build
# Nothing is compiled. See the header.
:

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{rtems_prefix}
# -a to preserve the symlinks and modes; the tree is full of them.
cp -a . $RPM_BUILD_ROOT%{rtems_prefix}/

# Fail loudly here rather than shipping a toolchain that cannot link the
# targets the IOCs actually build for.
for bsp in mvme2307 mvme3100; do
    test -d "$RPM_BUILD_ROOT%{rtems_prefix}/powerpc-rtems4.10/$bsp" || {
        echo "ERROR: BSP $bsp missing from the toolchain tree" >&2; exit 1; }
done
test -x "$RPM_BUILD_ROOT%{rtems_prefix}/bin/powerpc-rtems4.10-gcc" || {
    echo "ERROR: powerpc-rtems4.10-gcc not found under bin/" >&2; exit 1; }

%files
%defattr(-,root,root,-)
%dir %{rtems_prefix}
%{rtems_prefix}/*

%changelog
* Fri Aug 28 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 4.10-0
- Initial repackage of the frozen RTEMS 4.10 toolchain from
  /gem_sw/targetOS/RTEMS/rtems-4.10, for the EPICS 3.14 IOCs that cannot move
  to EPICS 7 / RTEMS 6. Installed at its original path so consuming builds
  need no path edits.
