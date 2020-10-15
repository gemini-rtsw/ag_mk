TOP=../..
include $(TOP)/configure/CONFIG

#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

# Search for .db files in $SYS_DB_PATHS, the list 
# of paths output by "convertGemRelease.pl dbPaths"
vpath %.db $(SYS_DB_PATHS)

DB  = ag_top.db
DB += simu_top.db
DB += ag_sadtop.db
DB += iocAdminRTEMS.db
DB += timeProbe.db
DB += agSeqTopGN.db
DB += agSeqTopGS.db
DB += agSeqSadTop.db
#DB += agSeqSiteDepGN.db
#DB += agSeqSiteDepGS.db
# DB += oiwfsgwTop.db

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
# DB += xxx.db
#TEMPLATES_DIR=schematics

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
$(COMMON_DIR)/%.db: %.db
	cp $< $@

clean::
	$(RM) *.dat *.bak
