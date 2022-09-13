#!/bin/bash

./test_channel l 10000 `pidof example` > tmp &

sleep 11

pkill test_channel

cat tmp | awk -F : '{print $6}' > load_sample
