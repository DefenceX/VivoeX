#!/bin/bash
PORT=5004
HEIGHT=480
WIDTH=640

pkill -f gst-launch-1.0

gst-launch-1.0 v4l2src device=/dev/video5 ! \
  video/x-raw, width=$WIDTH, height=$HEIGHT ! \
  videoconvert ! \
  queue ! \
  rtpvrawpay ! \
  udpsink host=239.192.1.1 port=$PORT &

# gst-launch-1.0 v4l2src device=/dev/video1 ! \
#   video/x-raw, width=$WIDTH, height=$HEIGHT ! \
#   videoconvert ! \
#   queue ! \
#   rtpvrawpay ! \
#   udpsink host=239.192.1.2 port=$PORT &

