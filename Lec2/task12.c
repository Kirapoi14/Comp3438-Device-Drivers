#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char * argv[]) {
    int i;
    pid_t childpid, sid;
    i = 0;

    childpid = fork();

    if (!childpid) {
        sid = setsid();
        if (sid < 0) {
            perror("setsid failed.");
            exit(EXIT_FAILURE);
        }
        
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while (1) {
            printf("%d.\n", i);
            i++;
            if (i % 100 == 0) sleep(1);
        }
    }
}