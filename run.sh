#!/bin/bash

gcc test.c -o test
make

# clear mmap_sample file
truncate --size 0 mmap_sample

echo "Running test program in background"
./test &

echo "Running perf trace mmap attach pid of test program in background for 2 seconds"
./main `pidof test` > mmap_sample &

sleep 2

pkill main
pkill test

make clean
