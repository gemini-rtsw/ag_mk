TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library


# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += genSubRecord
DBDINC += applyRecord
DBDINC += cadRecord
DBDINC += carRecord
DBDINC += sirRecord
DBDINC += menuCarstates
DBDINC += menuDirective
DBDINC += menuSimulation
DBDINC += cmdTimeoutRecord
DBDINC += lutinRecord
DBDINC += lutoutRecord
DBDINC += statusRecord


# install these .dbd files into <top>/dbd
DBD += genSubRecord.dbd
DBD += applyRecord.dbd
DBD += cadRecord.dbd
DBD += carRecord.dbd
DBD += sirRecord.dbd
DBD += menuCarstates.dbd
DBD += menuDirective.dbd
DBD += menuSimulation.dbd
DBD += cmdTimeoutRecord.dbd
DBD += lutinRecord.dbd
DBD += lutoutRecord.dbd
DBD += statusRecord.dbd
DBD += geminiRecords.dbd
DBD += lutFunc.dbd


# geminiRecords.dbd is made from all the individual .dbd files. 
geminiRecords_DBD += base.dbd
geminiRecords_DBD += genSubRecord.dbd
geminiRecords_DBD += applyRecord.dbd
geminiRecords_DBD += cadRecord.dbd
geminiRecords_DBD += carRecord.dbd
geminiRecords_DBD += sirRecord.dbd
geminiRecords_DBD += menuCarstates.dbd
geminiRecords_DBD += menuDirective.dbd
geminiRecords_DBD += menuSimulation.dbd
geminiRecords_DBD += cmdTimeoutRecord.dbd
geminiRecords_DBD += lutinRecord.dbd
geminiRecords_DBD += lutoutRecord.dbd
geminiRecords_DBD += statusRecord.dbd
geminiRecords_DBD += gemDevSoft.dbd

LIBRARY_IOC += geminiRecords
geminiRecords_SRCS += genSubRecord.c
geminiRecords_SRCS += applyRecord.c
geminiRecords_SRCS += cadRecord.c
geminiRecords_SRCS += carRecord.c
geminiRecords_SRCS += sirRecord.c
geminiRecords_SRCS += cmdTimeoutRecord.c
geminiRecords_SRCS += lutinRecord.c
geminiRecords_SRCS += lutoutRecord.c
geminiRecords_SRCS += statusRecord.c
geminiRecords_SRCS += devLutinSoft.c
geminiRecords_SRCS += devLutoutSoft.c
geminiRecords_SRCS += devStatusSoft.c

geminiRecords_LIBS += $(EPICS_BASE_IOC_LIBS)

INC += cad.h
INC += lut.h

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

