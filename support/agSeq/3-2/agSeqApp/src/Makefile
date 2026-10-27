TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#=============================
# Build a support module called <APPNAME>

LIBRARY_IOC += agSeq

# <APPNAME>.dbd will be created and installed
DBD += agSeq.dbd

# agSeq.dbd will be made up from these files:
agSeq_DBD += base.dbd
# List local .dbd files here
# agSeq_DBD += xxx.dbd
agSeq_DBD += timelib.dbd
agSeq_DBD += geminiRecords.dbd
agSeq_DBD += tcslib.dbd
agSeq_DBD += slalib.dbd
agSeq_DBD += agSeqRegisters.dbd

# Include dbd files for external support modules:
# agSeq_DBD += genSubRecord.dbd

# specify all source files to be compiled
# including sequencer (.st) source files
#agSeq_SRCS += xxx.c
#agSeq_SRCS += xxx.st
agSeq_SRCS += agSeq.c
agSeq_SRCS += agSeqNiciSimulate.c
agSeq_SRCS += agSeqCarSimulate.c
agSeq_SRCS += agSeqNifsSimulate.c
agSeq_SRCS += agSeqF2Simulate.c
agSeq_SRCS += agSeqNiriSimulate.c
agSeq_SRCS += agSeqTransforms.c
agSeq_SRCS += agSeqNirsSimulate.c
agSeq_SRCS += agUtils.c

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

