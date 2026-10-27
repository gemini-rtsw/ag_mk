TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#=============================
# Build a support module called <APPNAME>

LIBRARY += tcslib

# <APPNAME>.dbd will be created and installed
DBD += tcslib.dbd

# tcslib.dbd will be made up from these files:
tcslib_DBD += base.dbd
tcslib_DBD += geminiRecords.dbd
tcslib_DBD += tcslibFunc.dbd
tcslib_DBD += slalib.dbd
tcslib_DBD += astlib.dbd
# List local .dbd files here
# tcslib_DBD += xxx.dbd

# Include dbd files for external support modules:
# tcslib_DBD += genSubRecord.dbd

# specify all source files to be compiled
# including sequencer (.st) source files
# Add the source code files to this variable. The default has all .c files 
SRCS.c  = $(wildcard ../*.c)
tcslib_SRCS += $(strip $(patsubst ../%.c,    %.o, $(SRCS.c)))
#tcslib_SRCS += tcsCadSupport.c
#tcslib_SRCS += dbMatchField.c
#tcslib_SRCS += xxx.st

#INCS.h  = $(wildcard ../*.h)
#INC += $(INCS.h)
INC +=  tcsCadSupport.h
INC +=  tcsChannelAccess.h
INC +=  tcsServo.h
INC +=  tcsSeqMacros.h
INC += tcsSeqConstants.h
INC += tcsRandom.h
INC += tcslib.h
INC += tcsDecode.h
INC += tcsSubsysDecode.h
INC += tcsSubsysCadSupport.h
INC += tcsConstants.h
INC += tcsLogSupport.h
#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

