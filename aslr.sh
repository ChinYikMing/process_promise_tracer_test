#!/bin/bash
if [ $# -eq 0 ]
then
	echo "0 to disable ASLR, > 0 to enable ASLR"
	exit
fi

if [ $1 -eq 0 ]
then
	echo 0 > /proc/sys/kernel/randomize_va_space
	echo "disable ASLR"
elif [ $1 -ge 1 ]
then
	echo 1 > /proc/sys/kernel/randomize_va_space
	echo "enable ASLR"
else
	echo "unsupport negative value"
fi
