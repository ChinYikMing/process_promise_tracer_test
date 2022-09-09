all:
	gcc call_mmap.c -fPIC -shared -o libtest.so
	gcc -o test test.c libtest.so
	cp libtest.so /usr/lib
clean:
	rm -rf test