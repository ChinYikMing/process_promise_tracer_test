#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

void do_write(int fd, char *buf){
	while(1){
		write(fd, buf, strlen(buf));
		lseek(fd, 0, SEEK_SET);
	}
}

int main(){
	int fd = open("./testfile", O_WRONLY);
	assert(fd != -1);

	char buf[1024] = "apple";
	printf("buf addr: %p\n", (void *) buf);

	do_write(fd, buf);
}
