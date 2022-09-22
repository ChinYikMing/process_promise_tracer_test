CC=gcc
CCFLAGS=-Wall -g

frame-capture: frame-capture.c
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -f frame-capture *.raw *.jpg
