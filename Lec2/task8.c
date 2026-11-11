#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void main(void) {
    int ret_from_fork, mypid, ret_from_exec;
    int wstatus;
    mypid = getpid();
    printf("Before forking, my PID is %d.\n", mypid);

    ret_from_fork = fork();

    if (!ret_from_fork) {
        printf("I am a child.\n");
        ret_from_exec = execl("/usr/bin/ls", "ls", "-l", "-t", "-a", NULL);
        printf("execl returns %d, errno = %d.\n", ret_from_exec, errno);
        perror("execl failed.");
    } else if (ret_from_fork > 0) {
        printf("I am a parent.\n");
        wait(&wstatus);
    } else {
        perror("fork failure.");
    }
} 