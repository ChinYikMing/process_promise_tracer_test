#include "perf_rb.h"
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <linux/perf_event.h>
#include <stdint.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define READ_MEMORY_BARRIER()   __builtin_ia32_lfence()

void *perf_rb_get(int perf_fd, size_t pages){
	 // create ring buffer
	void *rb = mmap(NULL, PERF_RB_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, perf_fd, 0);
	if(MAP_FAILED == rb){
		perror("mmap ring buffer");
		return NULL;
	}

	return rb;
}

struct perf_sys_read_sample {
	struct perf_event_header header;
	uint32_t pid, tid;
	uint64_t addr;
	uint64_t len;
	uint64_t pgoff;
	char filename[];
};

int perf_rb_read(void *rb, sample_t *sample){
	if(!rb){
		//fprintf(stderr, "ring buffer is NULL\n");
		return -EAGAIN;
	}
	
	// the metadata header
	struct perf_event_mmap_page *rb_meta = (struct perf_event_mmap_page *) rb;
	uint64_t head = rb_meta->data_head;
	uint64_t tail = rb_meta->data_tail;

	READ_MEMORY_BARRIER();
	assert(tail <= head);
	if(head == tail){
		//fprintf(stderr, "ring buffer is empty\n");
		return -EAGAIN;
	}

	bool available = false;

	while(tail < head){
		uint64_t pos = tail % (PAGE_SIZE * PERF_RB_SIZE);
		struct perf_sys_read_sample *ent = (struct perf_sys_read_sample *)((char*) rb + PAGE_SIZE /* meta page */ + pos);

		tail += ent->header.size; // skip header to read data

		if(ent->header.type == PERF_RECORD_MMAP && (ent->header.misc & PERF_RECORD_MISC_MMAP_DATA)){
			sample->pid = ent->pid;
			sample->buf_addr = ent->addr;
			sample->buf_size = ent->len;
			sample->buf_pgoff = ent->pgoff;
			strcpy(sample->filename, ent->filename);
			available = true;
			break;
		}
	}

	rb_meta->data_tail = tail; // update tail since kernel does not wrap

	return available ? 0 : -EAGAIN;
}

void perf_rb_put(int perf_fd, void *rb){
	if(perf_fd < 0 || !rb)
		return;
	
	int ret = munmap(rb, PERF_RB_SIZE);
	assert(ret == 0);
	ret = close(perf_fd);
	assert(ret == 0);
	return;
}
