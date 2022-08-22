#include <linux/perf_event.h>    /* Definition of PERF_* constants */
#include <linux/hw_breakpoint.h> /* Definition of HW_* constants */
#include <sys/syscall.h>         /* Definition of SYS_* constants */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include "event.h"
#include "perf_rb.h"
#include <errno.h>
#include <stdbool.h>
#include <assert.h>

void usage(const char *prog_name);
int perf_event_open(struct perf_event_attr *attr, pid_t pid, int cpu, int group_fd, unsigned long flags);
void perf_event_register(struct perf_event_attr *attr, uint32_t type, event_t event);
int perf_event_enable(int perf_fd);
int perf_event_disable(int perf_fd);
int perf_event_start(int perf_fd);
int perf_event_stop(int perf_fd);
int perf_event_read(int perf_fd);

int main(int argc, char **argv){
	if(argc != 2)
		usage(argv[0]);

	assert(setvbuf(stdout, NULL, _IOLBF, 0) == 0);

	pid_t pid = (pid_t) strtol(argv[1], NULL, 10);
	//unsigned long period = (unsigned long) strtol(argv[2], NULL, 10);

	struct perf_event_attr attr;
	memset(&attr, 0, sizeof(struct perf_event_attr));
	perf_event_register(&attr, PERF_TYPE_TRACEPOINT, SYSCALL_MMAP);

	int perf_fd = perf_event_open(&attr, pid, -1, -1, 0);
	if(perf_fd == -1){
		perror("perf_event_open");
		exit(2);
	}

	if(perf_event_enable(perf_fd) == -1){
		perror("perf_event_enable");
		exit(3);
	}

	if(perf_event_start(perf_fd) == -1){
		perror("perf_event_start");
		exit(4);
	}
	
	/* if pid is 0, then the loop below will be accounted, otherwise nope */
	for(int i = 0; i < 100; i++){
		
	}

	void *rb = perf_rb_get(perf_fd, PERF_RB_SIZE);
	assert(rb != NULL);

	int ret;
	sample_t sample;
	
	while(true){
		ret = perf_rb_read(rb, &sample);

		if(ret == -EAGAIN){
			usleep(10000);
			continue;
		}

		printf("buf_addr: %lu, buf_size: %lu, buf_pgoff %lu, filename: %s\n", sample.buf_addr, 
										sample.buf_size,
										sample.buf_pgoff,
										sample.filename);
	}

	if(perf_event_stop(perf_fd) == -1){
		perror("perf_event_stop");
		exit(4);
	}

	if(perf_event_disable(perf_fd) == -1){
		perror("perf_event_disable");
		exit(3);
	}

	perf_rb_put(perf_fd, rb);

	exit(0);
}

int perf_event_open(struct perf_event_attr *attr, pid_t pid, int cpu, int group_fd, unsigned long flags){
	return syscall(__NR_perf_event_open, attr, pid, cpu, group_fd, flags);
}

void perf_event_register(struct perf_event_attr *attr, uint32_t type, event_t event){
	attr->size = sizeof(struct perf_event_attr);
	attr->type = type;
	attr->config = (uint64_t) event;
	attr->disabled = 1;
	attr->exclude_user = 0;
	attr->exclude_kernel = 1;
	attr->mmap_data = 1; /* mmap(2) calls with no PROT_EXEC */
	attr->sample_type = PERF_SAMPLE_TID | PERF_SAMPLE_ADDR;
	//attr.exclude_idle = 0;
}

int perf_event_enable(int perf_fd){

}

int perf_event_disable(int perf_fd){

}

int perf_event_start(int perf_fd){
	return ioctl(perf_fd, PERF_EVENT_IOC_ENABLE, 0);
}

int perf_event_stop(int perf_fd){
	return ioctl(perf_fd, PERF_EVENT_IOC_DISABLE, 0);
}

void usage(const char *prog_name){
	fprintf(stderr, "%s pid\n", prog_name);
	exit(1);
}
