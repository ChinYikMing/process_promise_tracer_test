CC=gcc
CCFLAGS=-Wall -g

frame-capture: frame-capture.c
	$(CC) $(CCFLAGS) $^ -o $@

jpg: frame-capture.c
	$(CC) $(CCFLAGS) -DRAW2JPG $^ -o frame-capture

clean:
	rm -f frame-capture *.raw *.jpg
