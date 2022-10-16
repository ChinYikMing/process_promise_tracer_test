# Run

## For MJPEG format:

* make mjpeg, compile the program with mjpeg format

* ./frame-capture, capture 10 raw frames from camera, ./frame-capture -c [frame_cnt] can change the frames count

* ./frame-capture -h, show usage

* make clean, remove all jpg images

## For YUYV format:

* make, compile the program without converting raw frames to jpg images

* make jpg, compile the program with converting raw frames to jpg images

* ./frame-capture, capture 10 raw frames from camera, ./frame-capture -c [frame_cnt] can change the frames count

* ./frame-capture -h, show usage

* make clean, remove all raw frames and jpg images

# Perf record memory of this program

* ../aslr.sh 0, turn off aslr

* make, compile the program without converting raw frames to jpg images

* perf record -d -c 1000 -e cpu/event=0xd0,umask=0x81/pp ./frame-capture -c 100, umask=0x81 is all_load event, umask=0x82 is all_store event

* perf report -D | grep PERF_RECORD_SAMPLE | grep "./frame-capture 印出的 mmap buffer addr, 應該是不會剛好，但是會落在範圍內"
