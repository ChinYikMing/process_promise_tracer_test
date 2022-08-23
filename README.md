clone 下來之後直接執行 ./run.sh （可能需要 root 權限）

然後 cat addr 和 cat mmap_sample 檔案，查看兩邊的記憶體是否一致（我這邊看到是一致）

addr 檔案是 test 應用程式 mmap 印出的記憶體，mmap_sample 檔案是 perf mmap record 得到的記憶體

備註： 1. test 應用程式會不斷 mmap 3 次，所以應該會有三個不同的記憶體
       2. 關閉 aslr 方便觀察


mem_match.sh
1. 分析 cheese camera 程式的 mmap
2. 執行 ./mem_match.sh 最後會看到 perf 追蹤到的 mmap 確實有對應到 cheese camera 程式的 mmap，但是觀察輸出的 filename 發現都是 so 檔案（dynamic shared object) ，沒辦法直接對應到 /dev/videoX

ideal/run.sh
1. 這是直接使用 v4l2 API 寫的 camera 程式
2. 執行 ./ideal/run.sh 最後會看到 filename 是 /dev/videoX

結論：
1. 要這樣來追蹤 mmap 可能局限 camera 程式必須直接使用 v4l2 API 而不能使用 library
2. 我在想 ptrace 能不能解決這個問題？？？
