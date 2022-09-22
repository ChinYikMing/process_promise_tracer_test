#!/bin/bash

args=("$@")
frame_cnt=${args[0]}

echo "Converting ${frame_cnt} raw frames to jpg"

for (( i=1; i<=${frame_cnt}; i++ ))
do
	ffmpeg -y -s:v 640x480 -pix_fmt yuyv422 -i "frame${i}.raw" "result${i}.jpg" > /dev/null 2>&1
done

echo "Done"
