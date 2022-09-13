1. 打開兩個terminal

2. 進到 camera_test 目錄，執行 make

3. 執行 ./example/make

4. 一個 terminal 執行 sudo ./camera_run

5. 一個 terminal 執行 sudo ./record_load_addr.sh

5. 重複以上，把 4 換成 sudo ./record_store_addr.sh

6. 比對 camera_output mmap 的 buffer 有沒有在 load_sample 和 store_sample 裡面
