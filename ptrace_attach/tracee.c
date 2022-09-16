#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

struct buf {
	void *start;
	int len;
} Buf[10];

int main(){
	int fd = open("testfile", O_RDONLY);
	assert(fd != -1);

	sleep(3);

	for(int i = 0; i < 3; i++){
		Buf[i].start = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
		Buf[i].len = 1024;
		assert(Buf[i].start != MAP_FAILED);
	}

	for(int i = 0; i < 3; i++){
		munmap(Buf[i].start, Buf[i].len);
	}

	return 0;
}
