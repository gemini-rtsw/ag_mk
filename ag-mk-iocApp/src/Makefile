TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC_RTEMS = ag-mk-ioc
# ag-mk-ioc.dbd will be created and installed
DBD += ag-mk-ioc.dbd

# ag-mk-ioc.dbd will be made up from these files:
ag-mk-ioc_DBD += base.dbd
ag-mk-ioc_DBD += iocAdmin.dbd
ag-mk-ioc_DBD += geminiRecords.dbd
ag-mk-ioc_DBD += pvload.dbd
#ag-mk-ioc_DBD += mbbipRecord.dbd
#ag-mk-ioc_DBD += loadRecord.dbd
#ag-mk-ioc_DBD += oiwfsgw.dbd
ag-mk-ioc_DBD += agSeq.dbd
ag-mk-ioc_DBD += pmaclib.dbd
ag-mk-ioc_DBD += bancomm.dbd
ag-mk-ioc_DBD += xy240.dbd
ag-mk-ioc_DBD += timelib.dbd
ag-mk-ioc_DBD += slalib.dbd
ag-mk-ioc_DBD += tcslib.dbd
ag-mk-ioc_DBD += timeProbe.dbd
ag-mk-ioc_DBD += menuScan.dbd
ag-mk-ioc_DBD += devIocStats.dbd
ag-mk-ioc_DBD += ag.dbd
ag-mk-ioc_DBD += iocInit.dbd

# ag-mk-ioc_registerRecordDeviceDriver.cpp derives from ag-mk-ioc.dbd
ag-mk-ioc_SRCS += ag-mk-ioc_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
ag-mk-ioc_SRCS_DEFAULT += ag-mk-iocMain.cpp

ag-mk-ioc_SRCS += ag_cad2.c
ag-mk-ioc_SRCS += ag_cad.c
ag-mk-ioc_SRCS += ag_cadcc.c
ag-mk-ioc_SRCS += ag_carhealth.c
ag-mk-ioc_SRCS += ag_hardw.c
ag-mk-ioc_SRCS += ag_gensub.c
ag-mk-ioc_SRCS += ag_globals.c
ag-mk-ioc_SRCS += ag_logg.c
ag-mk-ioc_SRCS += ag_mem.c
ag-mk-ioc_SRCS += ag_sad.c
ag-mk-ioc_SRCS += agSimulate.c
#ag-mk-ioc_SRCS += ag_test2.c
#ag-mk-ioc_SRCS += ag_test.c
ag-mk-ioc_SRCS += ag_track.c
ag-mk-ioc_SRCS += ag_utils.c
ag-mk-ioc_SRCS += cicsCALib.c
ag-mk-ioc_SRCS += cicsDBLib.c
ag-mk-ioc_SRCS += cicsLib.c

ag-mk-ioc_SRCS += initTrace.c

LIBRARY_IOC += agSupport
agSupport_SRCS += agcc.st
agSupport_SRCS += comp1.st

# Add all the support libraries used by this IOC

ag-mk-ioc_LIBS += geminiRecords
ag-mk-ioc_LIBS += pvload
ag-mk-ioc_LIBS += bancomm
ag-mk-ioc_LIBS += xy240
# ag-mk-ioc_LIBS += oiwfsgw
ag-mk-ioc_LIBS += agSeq
ag-mk-ioc_LIBS += pmaclib
ag-mk-ioc_LIBS += tcslib
ag-mk-ioc_LIBS += timelib
ag-mk-ioc_LIBS += slalib
ag-mk-ioc_LIBS += devIocStats
ag-mk-ioc_LIBS += timeProbe
ag-mk-ioc_LIBS += seq pv

# Finally link to the EPICS Base libraries
ag-mk-ioc_LIBS += agSupport

ag-mk-ioc_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

