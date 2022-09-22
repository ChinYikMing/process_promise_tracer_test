#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

void do_read(FILE *fptr, char *buf){
	while(1){
		fread(buf, 1, 1024, fptr);
		fseek(fptr, 0, SEEK_SET);
	}
}

int main(){
	FILE *fptr = fopen("./testfile", "r");
	assert(fptr != NULL);
	printf("fptr addr: %p\n", (void *) fptr);

	char buf[1024] = {0};
	printf("buf addr: %p\n", (void *) buf);

	do_read(fptr, buf);
}
