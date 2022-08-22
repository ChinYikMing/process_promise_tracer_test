clone 下來之後直接執行 ./run.sh （可能需要 root 權限）

然後 cat addr 和 cat mmap_sample 檔案，查看兩邊的記憶體是否一致（我這邊看到是一致）

addr 檔案是 test 應用程式 mmap 印出的記憶體，mmap_sample 檔案是 perf mmap record 得到的記憶體

備註： 1. test 應用程式會不斷 mmap 3 次，所以應該會有三個不同的記憶體
       2. 關閉 aslr 方便觀察
