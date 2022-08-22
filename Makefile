all:
	gcc main.c perf_rb.c -o main

clean:
	rm -f main test
