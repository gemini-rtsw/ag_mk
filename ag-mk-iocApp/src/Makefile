TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = ag-mk-ioc
# ag-mk-ioc.dbd will be created and installed
DBD += ag-mk-ioc.dbd

# ag-mk-ioc.dbd will be made up from these files:
ag-mk-ioc_DBD += base.dbd
# ag-mk-ioc_DBD += mbbipRecord.dbd

# Include dbd files from all support modules:
ag-mk-ioc_DBD += asSupport.dbd

# Add all the support libraries used by this IOC
# ag-mk-ioc_LIBS += xxx
# ag-mk-ioc_LIBS += seq pv seqDev
ag-mk-ioc_LIBS += devIocStats
ag-mk-ioc_LIBS += geminiRecords
ag-mk-ioc_LIBS += bancomm.dbd
ag-mk-ioc_LIBS += seq
ag-mk-ioc_LIBS += autosave
ag-mk-ioc_LIBS += timelib
ag-mk-ioc_LIBS += slalib
# Won't work for the host...
ag-mk-ioc_LIBS_RTEMS += pmaclib

# ag-mk-ioc_registerRecordDeviceDriver.cpp derives from ag-mk-ioc.dbd
ag-mk-ioc_SRCS += ag-mk-ioc_registerRecordDeviceDriver.cpp

ag-mk-ioc_SRCS += cicsLib.c
ag-mk-ioc_SRCS += cicsCALib.c
ag-mk-ioc_SRCS += cicsDBLib.c
ag-mk-ioc_SRCS += ag_pmac.c
ag-mk-ioc_SRCS += ag_globals.c
ag-mk-ioc_SRCS += ag_mem.c
ag-mk-ioc_SRCS += ag_hardw.c
ag-mk-ioc_SRCS += agSimulate.c
ag-mk-ioc_SRCS += ag_utils.c
ag-mk-ioc_SRCS += ag_carhealth.c
ag-mk-ioc_SRCS += ag_track.c
ag-mk-ioc_SRCS += ag_logg.c
ag-mk-ioc_SRCS += ag_cad.c
ag-mk-ioc_SRCS += ag_cad2.c
ag-mk-ioc_SRCS += ag_cadcc.c
ag-mk-ioc_SRCS += ag_gensub.c
ag-mk-ioc_SRCS += ag_sad.c
ag-mk-ioc_SRCS += ag_test.c
ag-mk-ioc_SRCS += pmacUpDown.c
ag-mk-ioc_SRCS += mbbipRecord.c

# Build the main IOC entry point on workstation OSs.
ag-mk-ioc_SRCS_DEFAULT += ag-mk-iocMain.cpp

# Finally link to the EPICS Base libraries
ag-mk-ioc_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

