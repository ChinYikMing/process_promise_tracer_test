CC=gcc
CCFLAGS=-Wall -g

frame-capture: frame-capture.c
	$(CC) $(CCFLAGS) $^ -o $@

mjpeg: frame-capture.c
	$(CC) $(CCFLAGS) -DMJPEG $^ -o frame-capture

jpg: frame-capture.c
	$(CC) $(CCFLAGS) -DRAW2JPG $^ -o frame-capture

clean:
	rm -f frame-capture *.raw *.jpg
