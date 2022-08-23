#!/bin/bash

make

./main &

./perf_mmap `pidof main` > mmap_sample &

sleep 10

pkill main
pkill perf_mmap

make clean

cat mmap_sample
