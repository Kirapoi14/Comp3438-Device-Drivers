#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void) {
    int ret_from_fork, mypid;
    mypid = getpid();

    ret_from_fork = fork();
    sleep(1);

    printf("After forking, my PID is %d, my PPID is %d, mypid = %d, fork() returns %d.\n", getpid(), getppid(), mypid, ret_from_work);
}