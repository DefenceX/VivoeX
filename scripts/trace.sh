#!/bin/bash 
export LD_PRELOAD=liblttng-ust-cyg-profile.so
lttng-sessiond --daemonize
lttng create vivoe-trace
lttng enable-event -u -a
lttng add-context -u -t vpid -t vtid -t procname
lttng enable-event --userspace vivoe_lite:*
lttng enable-event --userspace lttng_ust_cyg_profile:*
lttng start
$1
lttng list --userspace
lttng destroy