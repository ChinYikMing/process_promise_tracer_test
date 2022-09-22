#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void do_cp(char *dest, char *src){
	int src_len = strlen(src);
	int index = 0;

	while(1){
		dest[index] = src[index];
		index += 1;
		if(index == src_len)
			index = 0;
	}
}

int main(){
	int ret = fork();
	if(ret == 0){ // child
		char src[1024] = "apple";
		printf("src addr: %p\n", (void *) src);

		char dest[1024];
		printf("dest addr: %p\n", (void *) dest);

		do_cp(dest, src);
	} else { // parent
		int child_status;

		wait(&child_status);
	}

	return 0;
}
