#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void) {
    printf("My PID is %d.\n", getpid());
    printf("My PPID is %d.\n", getppid());
    printf("My UID is %d.\n", getuid());
}