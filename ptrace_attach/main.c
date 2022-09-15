#include "headers.h"

int STOPPED     = 0;
int TERMINATED  = 1;

typedef struct buffer {
	void *start;
	size_t len;
} buffer_t;

const char *callname(long call);
int ptrace_wait_syscall(pid_t pid);
long _ptrace(int request, pid_t pid, void* addr, void* data);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, " Usage: $ %s  <PID> \n", argv[0]);
        return EXIT_FAILURE;
    }
    pid_t pid = atoi(argv[1]);
    _ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    fprintf(stderr, " [TRACE] Attached to process. Ok. \n");
    
    _ptrace(PTRACE_SETOPTIONS, pid, NULL, (void*) PTRACE_O_TRACECLONE);
    _ptrace(PTRACE_SETOPTIONS, pid, NULL, (void*) PTRACE_O_TRACESYSGOOD);

    struct user_regs_struct regs;
    fprintf(stderr, " [TRACE] Start event loop. Ok. \n");
    for(;;) {
        // Intercept system call entry 
        if (ptrace_wait_syscall(pid) == TERMINATED) { 
            fprintf(stderr, " [TRACE] (1) Monitored process has terminated. \n");
            break;
        }

        // Intercept system call exit 
        if (ptrace_wait_syscall(pid) == TERMINATED) {                  
            fprintf(stderr, " [TRACE] (2) Monitored process has terminated. \n");
            break;
        }

        _ptrace(PTRACE_GETREGS, pid, NULL, &regs);

        // Get system call number
        int syscall = regs.orig_rax;
        if (syscall == SYS_mmap) {
            fprintf(stderr, "rdi: %lld\n", regs.rdi);
            fprintf(stderr, "rsi: %lld\n", regs.rsi);
            fprintf(stderr, "rdx: %lld\n", regs.rdx);
            fprintf(stderr, "r10: %lld\n", regs.r10);
            fprintf(stderr, "r8 : %lld\n", regs.r8);
            fprintf(stderr, "r9 : %lld\n", regs.r9);
            continue;        
        }
    }
    return 0;
}

long _ptrace(int request, pid_t pid, void* addr, void* data) {
    long r = ptrace((enum __ptrace_request)request, pid, addr, data);
    if (r == -1) {
        fprintf(stderr,  " [TRACE FAILURE] \n errno = %d\n msg   = %s\n", errno, strerror(errno));
        exit(0);
    }
    return r;
}

int ptrace_wait_syscall(pid_t pid) {
    int  status;

    for (;;) {
        _ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) { return TERMINATED; }
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80) { return STOPPED; }
    }
}