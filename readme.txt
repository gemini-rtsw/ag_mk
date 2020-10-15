
#
# To connect to sim3: telnet 10.1.5.85 2303
# Bootbar @ telnet 10.1.5.85 login:pass super:super
#

# Switch tcc's code
configure-ioc -t work \
  -b /gem_sw/test/tcumming/ioc/ag/mk/bin/RTEMS-mvme2307/ag-mk-ioc.boot \
  -s /gem_sw/test/tcumming/ioc/ag/mk/bin/RTEMS-mvme2307/stag-mk-IOC.boot  \
  sim3

# Switch back to hawi's code
configure-ioc -t work \
  -b /gem_sw/test/hstecher/ag.sim/ag/mk/bin/RTEMS-mvme2307/ag-mk-ioc.boot \
  -s /gem_sw/test/hstecher/ag.sim/ag/mk/bin/RTEMS-mvme2307/stag-sim-mk-ioc.boot \
  sim3

# Boot ag test code on real ag from my home directory.

configure-ioc -t work \
  -b /gem_sw/test/tcumming/ioc/ag/mk/bin/RTEMS-mvme2307/ag-mk-ioc.boot \
  -s /gem_sw/test/tcumming/ioc/ag/mk/bin/RTEMS-mvme2307/stag-mk-ioc.boot \
  ag-mk-ioc

# Boot from gwork on sim3

configure-ioc -t work \
  -b /gem_sw/work/R3.14.12.8/ioc/ag/mk/bin/RTEMS-mvme2307/ag-mk-ioc.boot \
  -s /gem_sw/work/R3.14.12.8/ioc/ag/mk/bin/RTEMS-mvme2307/stag-sim-mk-ioc.boot \
  sim3

# Boot test code

configure-ioc -t prod \
  -b /gem_sw/work/R3.14.12.8/ioc/ag/mk/bin/RTEMS-mvme2307/ag-mk-ioc.boot \
  -s /gem_sw/work/R3.14.12.8/ioc/ag/mk/bin/RTEMS-mvme2307/stag-mk-ioc.boot \
  ag-mk-ioc

# Boot back to original ag code

configure-ioc -t prod \
  -b /gem_sw/prod/R3.14.12.8/ioc/ag/mk/1-11/bin/RTEMS-mvme2307/ag-mk-ioc.boot \
  -s /gem_sw/prod/R3.14.12.8/ioc/ag/mk/1-11/bin/RTEMS-mvme2307/stag-mk-ioc.boot \
  ag-mk-ioc

