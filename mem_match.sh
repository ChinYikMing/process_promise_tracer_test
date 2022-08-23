#!/bin/bash

./cheese.sh

sed -n '1181,1292 p' cheesetracemem | grep mmap > tmp # 查看 strace -e trace=memory 發現這些行數是 cheese camera 會呼叫 mmap

awk -F = '{if(length($2) > 2) print $2}' tmp > mem # 過濾出 mmap return 的 memory 當作 mmap_sample 的 key

cat mmap_sample | grep -f mem --color=always # 把 mem 檔案每一行的 memory 當作 key 去 mmap_sample 搜尋
