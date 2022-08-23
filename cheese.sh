#!/bin/bash

gcc test.c -o test
make

# clear mmap_sample file
truncate --size 0 mmap_sample

echo "Running cheese program in background"
cheese &

echo "Running perf trace mmap attach pid of cheese program in background for 2 seconds"
./main `pidof cheese` > mmap_sample &

sleep 3

pkill main
pkill cheese

make clean
