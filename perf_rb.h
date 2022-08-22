#ifndef PERF_MMAP_HDR
#define PERF_MMAP_HDR

#define PAGE_SIZE 4096      // fix me with sysconf()
#define PERF_RB_PAGE 1+16 // according to man 2 perf_event_open, ring buffer size must be 1+2^n pages where the first page is the metadata page(struct perf_event_mmap_page)
#define PERF_RB_SIZE PERF_RB_PAGE * PAGE_SIZE

#include <stdint.h>
#include <stddef.h>

typedef struct sample {
	uint32_t cpu;
	uint32_t pid;
	uint64_t buf_addr; 
	uint64_t buf_size;  
	uint64_t buf_pgoff;
	char filename[];
} sample_t;

void *perf_rb_get(int perf_fd, size_t pages);
int perf_rb_read(void *rb, sample_t *sample);
void perf_rb_put(int perf_fd, void *rb);

#endif
