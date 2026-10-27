# epics-base-314.spec -- Gemini EPICS base R3.14.12.8, host + RTEMS 4.10 cross
#
# A REPACKAGE, not a build. The collected tree has NO src/ -- it is the
# installed product, not the source (confirmed in
# packaging/ade-collect/MANIFEST.txt, section 2). What it does have is every
# target already cross-built:
#
#     lib/linux-x86_64  lib/RTEMS-mvme2307  lib/RTEMS-mvme3100
#     lib/RTEMS-beatnik lib/RTEMS-mvme5500
#
# 15 libraries per RTEMS target. So there is nothing to compile and nothing to
# gain by trying: the artifacts we need already exist and are the exact ones
# production was built against.
#
# INSTALL PATH: the original /gem_sw/epics/R3.14.12.8/base.
# Only two files in the whole tree carry an absolute path
# (configure/CONFIG_SITE's INSTALL_LOCATION and
# configure/os/CONFIG_SITE.Common.RTEMS's RTEMS_BASE), so relocating is
# possible -- but every IOC's configure/RELEASE already points here, and
# keeping the path means the IOC sources build in CI with no edits at all.
#
# Named "epics-base-314", NOT "epics-base". The rpm-repo already holds
# epics-base-7.0.7 (/gem_base/epics/epics-base) and a host-only
# epics-base-3.14.12 (/gemsoft/opt/epics/base). Three names, three prefixes,
# no file conflicts, and pins in consuming specs stay unambiguous.

%global _enable_debug_package 0
%global debug_package %{nil}
# Prebuilt host and cross binaries: skip the post-install processing that would
# strip the PowerPC archives or fail on them.
%global __os_install_post %{nil}
%global _missing_build_ids_terminate_build 0
%global _binaries_in_noarch_packages_terminate_build 0

%define epics_ver     3.14.12.8
%define prefix_dir    /gem_sw/epics/R%{epics_ver}/base
%define cross_archs   RTEMS-mvme2307 RTEMS-mvme3100
# Provenance stamp. $GIT_HASH first (build_rpm.sh / build-and-upload.sh export
# it), then git, then a fixed fallback naming the source tree this was
# repackaged from -- the /gem_sw snapshot dated 2019-07-03. The generic "nogit"
# would be a poor permanent name: rpm-repo scratch tags are keyed on the full
# NVRA and never overwrite, so whatever Release ships here is forever.
%define git_hash %(if [ -n "$GIT_HASH" ]; then echo "$GIT_HASH"; else git rev-parse --short HEAD 2>/dev/null || echo gem20190703; fi)

Name:           epics-base-314
Version:        3.14.12.8
Release:        0.%{git_hash}%{?dist}
Summary:        EPICS base R3.14.12.8 (Gemini), host and RTEMS 4.10 cross builds
License:        EPICS Open License
Source0:        epics-base-R3.14.12.8-prebuilt.tar.gz
BuildArch:      noarch

BuildRequires:  tar gzip findutils coreutils

# As in rtems410: this is a prebuilt tree, and letting rpm derive dependencies
# from its binaries yields /usr/local/bin/perl (a shebang in a packaged script)
# and libreadline.so.6 (needed by the HOST softIoc/caget, which a cross build
# never runs). Neither exists on Rocky 9 and neither is required to compile
# against the cross libraries.
AutoReqProv:    no

# The cross libraries here were linked by this toolchain, and
# configure/os/CONFIG_SITE.Common.RTEMS points at
# /gem_sw/targetOS/RTEMS/rtems-4.10, which is where rtems410 installs.
# Deliberately unversioned: the toolchain is frozen, and an exact pin here
# would have to track this package's own Release string. The pipeline README
# says the same -- keep runtime Requires loose for cross-compiled content.
Requires:       rtems410

%description
EPICS base R3.14.12.8 as patched and used at Gemini, with the host
(linux-x86_64) and RTEMS 4.10 cross builds for mvme2307, mvme3100, mvme5500 and
beatnik.

The mvme2307 target is a Gemini addition -- stock EPICS 3.14.12 ships
mvme2100/2700/3100/5500 only -- which is why the shared epics-base-3.14.12
package cannot be used for the A&G and other VME IOCs.

Also carries Gemini's own build rules (configure/CONFIG.Gem, RULES.Gem and
bin/linux-x86_64/convertGemRelease.pl), so this package does NOT depend on
gemini-ade for them.

%package devel
Summary:        Headers, build rules and templates for %{name}
Requires:       %{name} = %{version}-%{release}
Requires:       rtems410
%description devel
Headers, configure/ build rules and templates needed to compile an IOC or
support module against EPICS base R3.14.12.8.

%prep
%setup -q -n base

%build
# Nothing is compiled. See the header.
:

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{prefix_dir}
cp -a . $RPM_BUILD_ROOT%{prefix_dir}/

# Refuse to ship a base that is missing the cross builds. That failure mode is
# exactly what makes the existing epics-base-3.14.12 package useless here, and
# it stays invisible until an IOC fails to link.
for a in %{cross_archs}; do
    test -d "$RPM_BUILD_ROOT%{prefix_dir}/lib/$a" || {
        echo "ERROR: lib/$a missing -- refusing to package a host-only base" >&2
        exit 1; }
done
# The Gemini rules are what make an IOC's configure/CONFIG work at all.
for f in configure/CONFIG.Gem configure/RULES.Gem bin/linux-x86_64/convertGemRelease.pl; do
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
* Fri Aug 28 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 3.14.12.8-0
- Initial packaging of the Gemini EPICS 3.14.12.8 base, repackaged from the
  installed tree at /gem_sw/epics/R3.14.12.8/base (no source tree exists) and
  installed at that same path so consuming IOCs need no configure/RELEASE edits.
