#ifndef BASIS_HDR
#define BASIS_HDR

#include <linux/perf_event.h>

//Note: be careful with endianess, below constant are all little endian on intel platform

typedef enum event {
	// hardware
	ALL_BRANCHES = 0x04C4,
	ALL_BRANCHES_MISS = 0x04C5,
	ALL_CYCLES = 0x01C0,
	ALL_INSTRUCTIONS = PERF_COUNT_HW_INSTRUCTIONS,

	// software
	
	// tracepoint
	SYSCALL_READ = 696, // from /sys/kernel/debug/tracing/events/syscalls/sys_enter_read/id
	SYSCALL_MMAP = 101,
	
	// hardware cache

	// raw
	ALL_LOADS = 0x81D0,
	ALL_STORES = 0x82D0

	// breakpoint
	
	// kprobe or uprobe
} event_t;
#endif
