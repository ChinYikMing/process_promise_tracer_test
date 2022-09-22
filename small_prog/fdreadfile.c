#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

void do_read(int fd, char *buf){
	while(1){
		read(fd, buf, 1024);
		lseek(fd, 0, SEEK_SET);
	}
}

int main(){
	int fd = open("./testfile", O_RDONLY);
	assert(fd != -1);

	char buf[1024] = {0};
	printf("buf addr: %p\n", (void *) buf);

	do_read(fd, buf);
}
