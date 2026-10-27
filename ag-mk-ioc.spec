# ag-mk-ioc.spec -- Gemini North Acquisition & Guidance IOC (EPICS 3.14.12.8)
#
# This IOC cannot move to EPICS 7 / RTEMS 6, so it builds against the frozen
# 3.14 world published as two shared RPMs:
#
#     rtems410        RTEMS 4.10 cross-toolchain  -> /gem_sw/targetOS/RTEMS/rtems-4.10
#     epics-base-314  EPICS base R3.14.12.8       -> /gem_sw/epics/R3.14.12.8/base
#
# Both install at their ORIGINAL production paths, and the 14 support modules
# vendored under support/ are symlinked into /gem_sw/prod/R3.14.12.8/support by
# build-support.sh. The consequence is that NO configure/RELEASE is edited
# anywhere -- not this IOC's, not any module's. The tree builds identically in
# CI, in a local build_rpm.sh run, and in the dev container, and every source
# stays byte-identical to what production was built from.

%define name    ag-mk-ioc
%define arch    %(uname -m)

# DEPLOYMENT LAYOUT -- no redirector, no symlinks, version comes from rpm.
#
# The board's PPCBug NVRAM holds these two, so they cannot move without
# reconfiguring every board:
#     Boot File     /gem_sw/prod/redirector/ag-mk-ioc
#     Argument File 10.2.71.12:/gem_sw:prod/redirector/ag-mk-ioc.cmd
# This package therefore installs REAL FILES at those paths, rather than the
# hand-maintained symlink that used to point into a versioned directory. Then
# `dnf upgrade` swaps the boot image atomically, `rpm -qf` says what is
# deployed, and `dnf downgrade` is a genuine rollback.
#
# The IOC tree itself goes to an UNVERSIONED path. It used to be
# .../ioc/ag/mk/1-20, which is why the .cmd had a version baked into it;
# with rpm the version belongs to the package, not the path.
%define instdir /gem_sw/prod/R3.14.12.8/ioc/ag/mk
%define bootdir /gem_sw/prod/redirector
%define _prefix %{instdir}

# Cross-compiled RTEMS objects must not go through the debuginfo machinery or
# be stripped -- they are PowerPC and never execute on the build host.
%global _enable_debug_package 0
%global debug_package %{nil}
%global __os_install_post /usr/lib/rpm/brp-compress %{nil}

%define git_hash %(if [ -n "$GIT_HASH" ]; then echo "$GIT_HASH"; else git rev-parse --short HEAD 2>/dev/null || echo nogit; fi)

Summary: Gemini North A&G IOC (EPICS 3.14.12.8, RTEMS 4.10 / mvme2307)
Name:    %{name}
Version: 1.20
Release: 0.git.%{git_hash}%{?dist}
License: EPICS Open License
Group:   Applications/Engineering
Source0: %{name}-%{version}.tar.gz
ExclusiveArch: %{arch}
Prefix:  %{_prefix}

## Pinned exactly, with %{?dist}: the rpm-repo is flat, so an unversioned
## dependency resolves to the highest EVR and .el9 sorts above .el8.
BuildRequires: epics-base-314-devel = 3.14.12.8-0.gem20190703%{?dist}
BuildRequires: rtems410             = 4.10-0.gem20190703%{?dist}
## db/ is NOT source -- it is generated from the .sch schematics by TDCT, a
## Java tool, at build time. Without these the build produces an IOC with no
## databases and fails at dbLoadRecords, not at compile time.
BuildRequires: tdct
BuildRequires: java-1.8.0-openjdk-headless
## The sequencer (seq 2-2-5-3) and its SNL compiler need these.
BuildRequires: re2c bison flex
BuildRequires: gcc gcc-c++ make perl-interpreter

## No runtime Requires. Everything shipped here is cross-compiled for the VME
## target and network-booted by the board; nothing in this package executes on
## the install host. Pinning the support modules as runtime deps would only
## create conflicts with co-installed IOCs pinning other versions.
AutoReqProv: no

%package devel
Summary: Developer environment hooks for %{name}
Requires: %{name} = %{version}-%{release}
%description devel
Build-environment glue for working on %{name} in the dev container. Contains
nothing the deployed IOC needs -- kept out of the main package so a production
boot server does not carry developer scripts.

%description
The Acquisition & Guidance IOC for Gemini North, cross-compiled for the
RTEMS-mvme2307 and RTEMS-mvme3100 VME targets.

Self-contained: the 14 EPICS 3.14 support modules it needs are vendored under
support/ and built from source as part of this package, because only a handful
of systems remain on EPICS 3.14 and packaging each module separately would cost
more than it saves.

%prep
%setup -q

%build
# Stage the vendored support modules into the production paths and build them
# in dependency order, then build the IOC itself. Shared with interactive use:
# the dev container runs the same script via /etc/profile.d/ag-mk-ioc.sh.
./build-support.sh

# INSTALL_LOCATION is what ends up inside the startup script. convertGemRelease.pl
# maps INSTALL_LOCATION -> TOP (line 155) and emits -MINSTALL="<abs_path>"
# (line 340), which msi substitutes into stag-mk-ioc.boot's `cd ${INSTALL}`.
# Building with the default ($(TOP), the rpmbuild BUILD dir) would bake a path
# that does not exist on the boot server, and the IOC would fail after loading.
make INSTALL_LOCATION=%{instdir}

%install
export DONT_STRIP=1
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{instdir} $RPM_BUILD_ROOT%{bootdir}

# The build installed into %{instdir} (see INSTALL_LOCATION above); take the
# tree from there so what we package is exactly what the boot script's baked-in
# paths refer to.
for d in bin db dbd lib configure iocBoot; do
    [ -d %{instdir}/$d ] && cp -r %{instdir}/$d $RPM_BUILD_ROOT%{instdir}/
done

B=$RPM_BUILD_ROOT%{instdir}/bin/RTEMS-mvme2307
# The boot image is the deliverable. If the cross link silently produced
# nothing, fail here rather than ship a package that only reveals itself when a
# board will not boot.
test -f "$B/ag-mk-ioc.boot"   || { echo "ERROR: no ag-mk-ioc.boot built" >&2; exit 1; }
test -f "$B/stag-mk-ioc.boot" || { echo "ERROR: no stag-mk-ioc.boot built" >&2; exit 1; }

# The startup script must not carry a versioned path any more -- that was the
# whole point of moving the version into rpm. Catch a regression here, not on
# the telescope.
if grep -qE '%{instdir}/[0-9]+-[0-9]+' "$B/stag-mk-ioc.boot"; then
    echo "ERROR: stag-mk-ioc.boot still has a versioned install path" >&2
    grep -nE '%{instdir}/[0-9]+-[0-9]+' "$B/stag-mk-ioc.boot" >&2
    exit 1
fi

# The two paths PPCBug reads from NVRAM. Real files, not symlinks.
cp "$B/ag-mk-ioc.boot" $RPM_BUILD_ROOT%{bootdir}/ag-mk-ioc
# RTEMS shell redirect: read startup commands from this file.
echo '< %{instdir}/bin/RTEMS-mvme2307/stag-mk-ioc.boot' \
    > $RPM_BUILD_ROOT%{bootdir}/ag-mk-ioc.cmd

# DEV ONLY -- goes in the -devel subpackage, never on a deployed host.
#
# Re-points the vendored support symlinks at the repo when a developer enters
# the dev container. build_rpm.sh mounts the repo at /work, dev_environment.sh
# at /repo, and the symlinks made during this build point into the rpmbuild
# BUILD directory, which is gone by the time the dev image is committed -- so
# they are broken in every dev container without this. Nothing at runtime
# resolves these paths: the board boots a statically linked RTEMS image with
# the support archives already linked in.
mkdir -p $RPM_BUILD_ROOT%{_sysconfdir}/profile.d
cat > $RPM_BUILD_ROOT%{_sysconfdir}/profile.d/ag-mk-ioc.sh <<'EOF'
for _d in /repo /work; do
    if [ -x "$_d/build-support.sh" ] && [ -d "$_d/support" ]; then
        "$_d/build-support.sh" --stage-only >/dev/null 2>&1 || true
        break
    fi
done
unset _d
EOF

%files
%defattr(-,root,root)
%{instdir}
# Deliberately NOT %config(noreplace): these carry the pointer to the version
# being booted, so an upgrade has to overwrite them. That is how a new release
# actually moves the board onto new code.
%{bootdir}/ag-mk-ioc
%{bootdir}/ag-mk-ioc.cmd

%files devel
%defattr(-,root,root)
%{_sysconfdir}/profile.d/ag-mk-ioc.sh

%changelog
* Mon Aug 31 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 1.20-0
- First GitHub pipeline build, migrated from SVN
  (http://sbfsvn02/gemini-sw/gem/trunk/ioc/ag/mk) with full history.
- Support modules vendored from /gem_sw/prod/R3.14.12.8/support at the
  versions pinned in configure/RELEASE.
