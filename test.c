#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#define MMAP_SIZE 8192

typedef struct buffer {
	void *start;
	size_t len;
} buffer_t;

int main(){
	buffer_t data[3];

	int fd = open("./testfile", O_RDWR);
	assert(fd != -1);

	FILE *addr_file = fopen("./addr", "w+");
	assert(addr_file != NULL);

	setvbuf(addr_file, NULL, _IOLBF, 0);

	char addr[1024];
	while(1){
		for(int i = 0; i < 3; i++){
			memset(addr, 0, sizeof(1024));

			data[i].start = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
			assert(data[i].start != MAP_FAILED);
			data[i].len = MMAP_SIZE;

			sprintf(addr, "data[%d]: %lu\n", i, (uint64_t) data[i].start);
			fwrite(addr, sizeof(char), strlen(addr), addr_file);

			//printf("data[%d]: %p\n", i, data[i].start);
		}

		sleep(1);

		for(int i = 0; i < 3; i++){
			munmap(data[i].start, data[i].len);
		}
	}
	
	return 0;
}
