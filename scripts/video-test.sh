#!/bin/bash
PORT=5004
HEIGHT=480
WIDTH=640
DEV=/dev/video0

if [ -z $1 ]; then
  OPTION="1"
else
  OPTION=$1
fi

echo "Selected Option $OPTION"

if [ "$OPTION" == "0" ]
then
  gst-launch-1.0 v4l2src device=$DEV ! \
    video/x-raw, width=$WIDTH, height=$HEIGHT ! \
    videoconvert ! \
    ximagesink
fi

if [ "$OPTION" == "1" ]
then
  gst-launch-1.0 videotestsrc ! \
    video/x-raw, format=UYVY, width=$WIDTH, height=$HEIGHT ! \
    queue ! \
    rtpvrawpay ! \
    udpsink host=127.0.0.1 port=$PORT
fi

if [ "$OPTION" == "2" ]
then
  gst-launch-1.0 v4l2src device=$DEV ! \
    video/x-raw, width=$WIDTH, height=$HEIGHT ! \
    videoconvert ! \
    queue ! \
    rtpvrawpay ! \
    udpsink host=127.0.0.1 port=$PORT
fi

if [ "$OPTION" == "3" ]
then
  gst-launch-1.0 -v udpsrc port=$PORT \
    caps="application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)RAW, sampling=(string)YCbCr-4:2:2, depth=(string)8, width=(string)$WIDTH, height=(string)$HEIGHT, payload=(int)96" ! \
    queue ! \
    rtpvrawdepay ! \
    queue ! \
    videoconvert ! \
    ximagesink
fi

if [ "$OPTION" == "4" ]
then
  file=$(ls ./videos/*.mp4)
  printf "Playing file $file\n"
  gst-launch-1.0 -v filesrc location=$file ! \
    decodebin ! \
    videoconvert ! \
    xvimagesink
fi

if [ "$OPTION" == "5" ]
then
  file=$(ls ./videos/*.mp4)
  printf "Playing file $file\n"

  gst-launch-1.0 -v filesrc location=$file ! \
    decodebin ! \
    videoconvert ! \
    videoscale ! \
    videorate ! \
    video/x-raw, format=UYVY, width=$WIDTH, height=$HEIGHT, framerate=28/1 ! \
    queue ! \
    rtpvrawpay ! \
    udpsink host=127.0.0.1 port=$PORT 
fi
