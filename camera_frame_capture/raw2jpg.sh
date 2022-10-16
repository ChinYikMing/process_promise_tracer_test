#!/bin/bash

args=("$@")
frame_cnt=${args[0]}
frame_name=""
result_name=""

echo "Converting ${frame_cnt} raw frames to jpg..."

for (( i=1; i<=${frame_cnt}; i++ ))
do
	if [ ${i} -le 9 ]
	then 
		frame_name="frame00000000${i}.raw"
		result_name="frame00000000${i}.jpg"
	elif [ ${i} -le 99 ]
	then 
		frame_name="frame0000000${i}.raw"
		result_name="frame0000000${i}.jpg"
	elif [ ${i} -le 999 ]
	then 
		frame_name="frame000000${i}.raw"
		result_name="frame000000${i}.jpg"
	elif [ ${i} -le 9999 ]
	then 
		frame_name="frame00000${i}.raw"
		result_name="frame00000${i}.jpg"
	elif [ ${i} -le 99999 ]
	then 
		frame_name="frame0000${i}.raw"
		result_name="frame0000${i}.jpg"
	elif [ ${i} -le 999999 ]
	then 
		frame_name="frame000${i}.raw"
		result_name="frame000${i}.jpg"
	elif [ ${i} -le 9999999 ]
	then 
		frame_name="frame00${i}.raw"
		result_name="frame00${i}.jpg"
	elif [ ${i} -le 99999999 ]
	then 
		frame_name="frame0${i}.raw"
		result_name="frame0${i}.jpg"
	elif [ ${i} -le 999999999 ]
	then 
		frame_name="frame${i}.raw"
		result_name="frame${i}.jpg"
	fi

	ffmpeg -y -s:v 640x480 -pix_fmt yuyv422 -i ${frame_name} ${result_name} > /dev/null 2>&1
done

echo "Done"
