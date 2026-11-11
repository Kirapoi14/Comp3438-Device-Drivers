#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void) {
    int i, n = 4;
    pid_t childpid;

    for (i = 1; i < n; i++)
        if (!(childpid = fork()))  break; // child suicide.
    printf("I am PID %d, PPID %d, i = %d.\n", getpid(), getppid(), i);
}