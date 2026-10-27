TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
vpath %.sym ..
vpath %-edb.def ..
vpath %-tdct.cfg ..
vpath %.db $(SYS_DB_PATHS)

# Install database files created from .sch files
# using TDCT (or just install .db files) into <top>/db.
# TDCT_CFG can be redefined here if needed
TDCT_CFG = ../tdct.cfg

# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += $(wildcard ../*.sym)
DB += $(wildcard ../*-edb.def)
DB += $(wildcard ../*-tdct.cfg)
DEPSCHS = $(wildcard ../*.sch)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
$(COMMON_DIR)/%.db: %.db
	cp $< $@

