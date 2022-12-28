#!/bin/bash 
echo "Did you build the code with 'cmake -DTRACE=ON ..' ?"
read -p "Press any key to continue... " -n1 -s
export LD_PRELOAD=liblttng-ust-cyg-profile.so
lttng-sessiond --daemonize
lttng create vivoe-trace
lttng enable-event -u -a
lttng add-context -u -t vpid -t vtid -t procname
lttng enable-event --userspace vivoe_lite:main
lttng enable-event --userspace vivoe_lite:app_callback
lttng enable-event --userspace lttng_ust_cyg_profile:func_entry
lttng enable-event --userspace lttng_ust_cyg_profile:func_exit
lttng enable-event --userspace lttng_ust_cyg_profile'*'
lttng start
$1
lttng list --userspace
lttng destroy