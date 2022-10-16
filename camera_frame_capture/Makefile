CC=g++
CCFLAGS=-Wall -g `pkg-config --cflags opencv4`
CCLIBS=`pkg-config --libs opencv4`

mjpeg: frame-capture.cpp
	$(CC) $(CCFLAGS) -DMJPEG $^ -o frame-capture $(CCLIBS)

video: *.jpg
	ffmpeg -framerate 30 -i frame%09d.jpg output.mp4	

playvideo: output.mp4
	ffplay output.mp4

showvideoinfo: output.mp4
	ffprobe output.mp4

yuyv: frame-capture.cpp
	$(CC) $(CCFLAGS) -DRAW2JPG $^ -o frame-capture $(CCLIBS)

clean:
	rm -f frame-capture *.raw *.jpg *.mp4
