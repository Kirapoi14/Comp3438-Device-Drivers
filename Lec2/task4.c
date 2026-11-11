#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void) {
    int ret_from_fork, mypid;
    mypid = getpid();
    printf("Before forking, my PID is %d.\n", mypid);

    ret_from_fork = fork();
    
    if (ret_from_fork == 0)
        printf("I am the child.\n");
    else if (ret_from_fork > 0)
        printf("I am the parent.\n");
    else
        printf("fork failure.");
}