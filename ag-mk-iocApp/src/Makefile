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

# Include dbd files from all support modules:
#ag-mk-ioc_DBD += xxx.dbd

# Add all the support libraries used by this IOC
# ag-mk-ioc_LIBS += xxx
# ag-mk-ioc_LIBS += seq pv seqDev

# ag-mk-ioc_registerRecordDeviceDriver.cpp derives from ag-mk-ioc.dbd
ag-mk-ioc_SRCS += ag-mk-ioc_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
ag-mk-ioc_SRCS_DEFAULT += ag-mk-iocMain.cpp

# Finally link to the EPICS Base libraries
ag-mk-ioc_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

