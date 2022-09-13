#!/bin/bash

./test_channel s 10000 `pidof example` > tmp &

sleep 11

pkill test_channel

cat tmp | awk -F : '{print $6}' > store_sample
