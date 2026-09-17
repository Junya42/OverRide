#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

void clear_stdin(void)
{
    char c = 0;

    while (1) {
        c = getchar();
        if (c == '\n' || c == (char)0xff)
            break;
    }
}

unsigned int get_unum(void)
{
    unsigned int n = 0;

    fflush(stdout);
    scanf("%u", &n);
    clear_stdin();
    return n;
}

void prog_timeout(void)
{
    asm("mov $1, %%eax; mov $1, %%ebx; int $0x80" ::: "eax", "ebx");
}

void enable_timeout_cons(void)
{
    signal(SIGALRM, (void *)prog_timeout);
    alarm(60);
}

int main(void)
{
    pid_t   pid;
    char    buf[128];
    int     status;
    int     syscall;

    pid = fork();
    memset(buf, 0, 128);
    syscall = 0;
    status = 0;

    if (pid == 0) {
        prctl(1, 1);                 /* PR_SET_PDEATHSIG, SIGHUP */
        ptrace(0, 0, 0, 0);          /* PTRACE_TRACEME */
        puts("Give me some shellcode, k");
        gets(buf);                   /* overflow */
    } else {
        while (1) {
            wait(&status);
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                puts("child is exiting...");
                break;
            }
            syscall = ptrace(3, pid, 0x2c, 0);   /* PEEKUSER, ORIG_EAX */
            if (syscall == 11) {                 /* execve */
                puts("no exec() for you");
                kill(pid, 9);
                break;
            }
        }
    }
    return 0;
}