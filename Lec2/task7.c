#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void main(void) {
    int i, n = 4;
    pid_t childpid;
    int status;
    int ret_from_wait;

    for (i = 1; i < n; i++)
        if (childpid = fork())  break; // parent suicide.
    do {
        ret_from_wait = wait(&status);
        printf("childpid = %d, returned from wait = %d.\n", childpid, ret_from_wait);
        if ((ret_from_wait == -1) && (errno != EINTR)) break;
    } while (childpid != ret_from_wait);

    printf("I am PID %d, PPID %d, i = %d.\n", getpid(), getppid(), i);
}