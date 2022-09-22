#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096

int main(){
	int fd = open("./testfile", O_RDWR);
	assert(fd != -1);

	void *ptr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	assert(ptr != MAP_FAILED);
	printf("ptr: %p\n", ptr);

	close(fd); // useless now

	char *cptr = (char *) ptr;
	while(1){
		//*(cptr + 3) = 'b'; // should see ptr + 3 address
		*cptr = 'b'; // should see ptr + 3 address
	}
}
