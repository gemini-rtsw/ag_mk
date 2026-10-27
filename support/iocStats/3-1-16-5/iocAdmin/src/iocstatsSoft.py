#!/usr/bin/python

import os
import sys
import subprocess

current_dir = os.path.dirname(os.path.realpath(__file__))
print current_dir
print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)
target_ioc = str(sys.argv[1])
ioc_top = str(sys.argv[2])
print ("Target IOC = %s") % target_ioc
print ("IOC Top = %s") % ioc_top

medm = '/gem_sw/epics/R3.14.12.8/extensions/bin/linux-x86_64/medm'
#Get the installed version...
# /gem_sw/prod/R3.14.12.8/support/iocStats/3-1-14-1/bin/linux-x86_64/../../op/adl/ioc_stats_rtems.adl
#iocstats = current_dir + '/../../op/adl/ioc_stats_rtems.adl'
iocstats = current_dir + '/../../op/adl/ioc_stats_soft.adl'
print iocstats
p1 = subprocess.Popen(['host', target_ioc], stdout=subprocess.PIPE)
p2 = subprocess.Popen(['awk', '/has address/ { print $4 ; exit}'], stdin=p1.stdout, stdout=subprocess.PIPE)
ipaddress = p2.communicate()[0]

if not ipaddress:
	print ("Could not lookup machine. Exiting...")
else:
	print ("Starting iocstats on %s ") % ipaddress
	os.environ["EPICS_CA_ADDR_LIST"] = ipaddress
	print os.environ["EPICS_CA_ADDR_LIST"]
	
	macro = '"ioc=' + ioc_top + '"'
	#print macro
	subprocess.Popen([medm, '-x', '-macro', macro, iocstats])

print "Done!"
sys.exit()

