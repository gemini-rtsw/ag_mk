TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = ag-mk-IOC
# ag-mk-IOC.dbd will be created and installed
DBD += ag-mk-IOC.dbd

# ag-mk-IOC.dbd will be made up from these files:
ag-mk-IOC_DBD += base.dbd

# Include dbd files from all support modules:
#ag-mk-IOC_DBD += xxx.dbd

# Add all the support libraries used by this IOC
# ag-mk-IOC_LIBS += xxx
# ag-mk-IOC_LIBS += seq pv seqDev

# ag-mk-IOC_registerRecordDeviceDriver.cpp derives from ag-mk-IOC.dbd
ag-mk-IOC_SRCS += ag-mk-IOC_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
ag-mk-IOC_SRCS_DEFAULT += ag-mk-IOCMain.cpp

# Finally link to the EPICS Base libraries
ag-mk-IOC_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

