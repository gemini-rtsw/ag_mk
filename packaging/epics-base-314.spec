# epics-base-314.spec -- Gemini EPICS base R3.14.12.8, host + RTEMS 4.10 cross
#
# Two halves, from two sources:
#
#   RTEMS cross builds (lib/RTEMS-*, bin/RTEMS-*)  -- REPACKAGED from the
#       installed production tree (Source0). There is no reason to rebuild them:
#       they are the exact artifacts production was built against, and the
#       RTEMS 4.10 toolchain that made them is frozen.
#
#   msi (bin/linux-x86_64/msi) -- BUILT on EL9 from the production extension
#       source (Source2). In 3.14 msi is an extension, not part of base; on the
#       Gemini hosts it is found on PATH from /gem_sw/epics/R3.14.12.8/extensions.
#       RULES.Db/RULES.Gem need it (iocStats, every .boot startup script).
#
#   Host build (bin/linux-x86_64, lib/linux-x86_64) -- REBUILT on EL9 from the
#       3.14.12.8 source (Source1). The prebuilt host binaries come from an
#       older EL and link libreadline.so.6, which Rocky 9 does not ship. libCom
#       links it, so every host tool was dead -- including dbExpand and msi,
#       which every IOC build runs. That was found by the first ag-mk-ioc build.
#
# The source was verified to be the same Gemini tree as the installed one:
# include/, dbd/ and db/ from a host build of Source1 are byte-identical to the
# prebuilt tree (only include/os/RTEMS differs, which a host-only build does not
# produce). The overlay below therefore replaces only files that exist in BOTH,
# so the Gemini additions the source does not build -- convertGemRelease.pl,
# gemTdct, CONFIG.Gem, RULES.Gem -- stay exactly as production had them, and
# the extras the rebuild produces (Perl CA bindings) are not shipped.
#
# TWO GEMINI CONFIG FILES ARE ADJUSTED for this environment, nothing else:
#   configure/CONFIG_SITE  gains  MSI = $(EPICS_BASE_HOST_BIN)/msi
#       so msi is found without putting the 3.14 tools on everyone's PATH.
#   configure/CONFIG.Gem   SYS_TDCT_PATHS gains $(TDCT)/library/{default_tdct,
#       epics,gemini}. The 2019 file only searched $(EPICS)/extensions/src/tdct/sym,
#       where production's tdct 2.17.5 kept every symbol; the tdct 2.18.6 RPM
#       splits them into library/. Without this TDCT silently skips every
#       hierarchical sub-schematic (inhier/hwin/hwout not found): ag_top.db came
#       out with 12 of its 2009 records and the build still "succeeded".
#
# INSTALL PATH: the original /gem_sw/epics/R3.14.12.8/base, so every IOC's and
# support module's configure/RELEASE resolves unchanged.
#
# Named "epics-base-314", NOT "epics-base", so it coexists with epics-base-7.0.7
# (/gem_base/epics/epics-base) and the host-only epics-base-3.14.12
# (/gemsoft/opt/epics/base).

%global _enable_debug_package 0
%global debug_package %{nil}
# The cross archives are PowerPC: skip post-install processing that would strip
# or choke on them.
%global __os_install_post %{nil}
%global _missing_build_ids_terminate_build 0

%define epics_ver     3.14.12.8
%define prefix_dir    /gem_sw/epics/R%{epics_ver}/base
%define cross_archs   RTEMS-mvme2307 RTEMS-mvme3100
%define host_arch     linux-x86_64

Name:           epics-base-314
Version:        3.14.12.8
# Release 2: adds msi and the CONFIG_SITE/CONFIG.Gem adjustments.
# Release 1: host half rebuilt for EL9. Release 0 was the straight repackage.
# Fixed rather than git-derived: rpm-repo tags are keyed on the full NVRA and
# never overwrite, and this names what it is -- the 2019 production snapshot.
Release:        2.gem20190703%{?dist}
Summary:        EPICS base R3.14.12.8 (Gemini), host and RTEMS 4.10 cross builds
License:        EPICS Open License
Source0:        epics-base-R3.14.12.8-prebuilt.tar.gz
Source1:        epics-base-R3.14.12.8-hostsrc.tar.gz
Source2:        msi-R3.14.12.8-src.tar.gz
ExclusiveArch:  x86_64

BuildRequires:  gcc gcc-c++ make perl readline-devel
BuildRequires:  tar gzip findutils coreutils

# Off because the cross half is a foreign prebuilt tree, and rpm would derive
# junk from it (e.g. /usr/local/bin/perl from a script shebang). The host half's
# real needs are therefore listed by hand.
AutoReqProv:    no
Requires:       readline
# The build scripts (convertRelease.pl, convertGemRelease.pl, ...) use FindBin,
# File::Copy, Getopt and other core modules that EL9's perl-interpreter leaves
# out; the "perl" metapackage brings the full core set.
Requires:       perl
# configure/os/CONFIG_SITE.Common.RTEMS points at
# /gem_sw/targetOS/RTEMS/rtems-4.10, where rtems410 installs. Unversioned: the
# toolchain is frozen, and runtime Requires stay loose for cross content.
Requires:       rtems410

%description
EPICS base R3.14.12.8 as patched and used at Gemini: host (linux-x86_64,
rebuilt for EL9) plus the production RTEMS 4.10 cross builds for mvme2307,
mvme3100, mvme5500 and beatnik.

The mvme2307 target is a Gemini addition -- stock EPICS 3.14.12 ships
mvme2100/2700/3100/5500 only -- which is why the shared epics-base-3.14.12
package cannot be used for the A&G and other VME IOCs.

Carries Gemini's build rules (configure/CONFIG.Gem, RULES.Gem,
bin/linux-x86_64/convertGemRelease.pl), so it does not depend on gemini-ade.

%package devel
Summary:        Headers, build rules and templates for %{name}
Requires:       %{name} = %{version}-%{release}
Requires:       perl
# EPICS links host libraries with -lreadline (COMMANDLINE_LIBRARY), which needs
# the unversioned libreadline.so from readline-devel.
Requires:       readline-devel
Requires:       rtems410
%description devel
Headers, configure/ build rules and templates needed to compile an IOC or
support module against EPICS base R3.14.12.8.

%prep
# Unpack both: base/ (prebuilt production tree) and base-3.14.12/ (source).
%setup -q -c -T -n %{name}-%{version} -a 0 -a 1 -a 2

%build
# Build the host half AT the install path. EPICS 3.14 bakes the library
# directory into each host binary's rpath, so building anywhere else would ship
# binaries that look for their libraries in the rpmbuild BUILD directory.
# This writes outside the buildroot, which is fine because the build always
# runs in a throwaway container (build_rpm.sh / build-and-upload.sh).
rm -rf %{prefix_dir}
mkdir -p $(dirname %{prefix_dir})
cp -a base-3.14.12 %{prefix_dir}
make -C %{prefix_dir} -j$(nproc) EPICS_HOST_ARCH=%{host_arch} CROSS_COMPILER_TARGET_ARCHS=

# msi, against the host base just built (its configure/RELEASE points at
# %{prefix_dir}). Drop the production build products the source tarball
# carries -- they link libreadline.so.6.
rm -rf msi/bin msi/lib msi/msiApp/src/O.*
make -C msi EPICS_HOST_ARCH=%{host_arch} CROSS_COMPILER_TARGET_ARCHS=

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{prefix_dir}
cp -a base/. $RPM_BUILD_ROOT%{prefix_dir}/

# Overlay: swap each prebuilt host file for its rebuilt counterpart. Only files
# present in BOTH are replaced -- see the header for why.
for d in bin/%{host_arch} lib/%{host_arch}; do
    for f in $RPM_BUILD_ROOT%{prefix_dir}/$d/*; do
        n=$(basename "$f")
        [ -e "%{prefix_dir}/$d/$n" ] || [ -L "%{prefix_dir}/$d/$n" ] || continue
        rm -f "$f"
        cp -a "%{prefix_dir}/$d/$n" "$f"
    done
done

install -m 0755 msi/bin/%{host_arch}/msi $RPM_BUILD_ROOT%{prefix_dir}/bin/%{host_arch}/msi

C=$RPM_BUILD_ROOT%{prefix_dir}/configure
chmod u+w $C/CONFIG_SITE $C/CONFIG.Gem
cat >> $C/CONFIG_SITE <<'MSIEOF'

# Added by the epics-base-314 RPM: msi is an extension in 3.14 and is not on
# PATH here. See the spec header.
MSI = $(EPICS_BASE_HOST_BIN)/msi
MSIEOF
sed -i 's|^export SYS_TDCT_PATHS = $(TDCT_PATHS2):$(EPICS)/extensions/src/tdct/sym$|export SYS_TDCT_PATHS = $(TDCT_PATHS2):$(TDCT)/sym:$(TDCT)/library/default_tdct:$(TDCT)/library/epics:$(TDCT)/library/gemini|' $C/CONFIG.Gem
# The sed must have matched: a silent no-op here reproduces the 12-of-2009 bug.
grep -q 'library/gemini' $C/CONFIG.Gem || { echo "ERROR: CONFIG.Gem TDCT path not patched" >&2; exit 1; }

# Nothing may still need readline 6 -- that was the whole point.
if grep -l 'libreadline\.so\.6' $RPM_BUILD_ROOT%{prefix_dir}/bin/%{host_arch}/* \
        $RPM_BUILD_ROOT%{prefix_dir}/lib/%{host_arch}/* 2>/dev/null; then
    echo "ERROR: host files above still link libreadline.so.6" >&2
    exit 1
fi

# Refuse to ship a base missing the cross builds -- the failure that makes the
# existing epics-base-3.14.12 package useless here, invisible until an IOC
# fails to link.
for a in %{cross_archs}; do
    test -d "$RPM_BUILD_ROOT%{prefix_dir}/lib/$a" || {
        echo "ERROR: lib/$a missing -- refusing to package a host-only base" >&2
        exit 1; }
done
# The Gemini rules are what make an IOC's configure/CONFIG work at all.
for f in configure/CONFIG.Gem configure/RULES.Gem bin/%{host_arch}/convertGemRelease.pl; do
    test -e "$RPM_BUILD_ROOT%{prefix_dir}/$f" || {
        echo "ERROR: $f missing from the base tree" >&2; exit 1; }
done

%files
%defattr(-,root,root,-)
%dir %{prefix_dir}
%{prefix_dir}/bin
%{prefix_dir}/lib
%{prefix_dir}/db
%{prefix_dir}/dbd
%{prefix_dir}/html

%files devel
%defattr(-,root,root,-)
%{prefix_dir}/include
%{prefix_dir}/configure
%{prefix_dir}/templates

%changelog
* Fri Oct 30 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 3.14.12.8-2.gem20190703
- Build msi from the production extension source and point MSI at it.
- Add tdct 2.18.6's library/ dirs to SYS_TDCT_PATHS in CONFIG.Gem; without
  them hierarchical schematics silently lost their sub-sheets.
- devel: Requires readline-devel for -lreadline in host links.

* Wed Oct 28 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 3.14.12.8-1.gem20190703
- (release 1) Rebuild the linux-x86_64 host half from the 3.14.12.8 source on EL9. The
  prebuilt host binaries linked libreadline.so.6, absent on Rocky 9, so every
  host build tool (dbExpand, msi, ...) failed and no IOC could build.
- Source verified identical to the production tree (include/, dbd/, db/).
- Add Requires: perl and readline, needed by the build scripts and libCom.
- Now x86_64 rather than noarch, since it carries EL9-native binaries.

* Fri Aug 28 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 3.14.12.8-0
- Initial packaging of the Gemini EPICS 3.14.12.8 base, repackaged from the
  installed tree at /gem_sw/epics/R3.14.12.8/base and installed at that same
  path so consuming IOCs need no configure/RELEASE edits.
