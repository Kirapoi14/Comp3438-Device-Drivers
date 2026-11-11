#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int status;
    pid_t childpid;
    childpid = fork();
    char * argv[3];
    argv[0] = "ls";
    argv[1] = "-l";
    argv[2] = NULL;

    if (childpid == -1) {
        perror("Error in the fork");
        exit(1);
    }
    else if (childpid == 0) {
        if (execvp("ls", argv) < 0) {
            perror("Exec of ls failed");
            exit(1);
        }
    }
    else if (childpid != wait(&status))
        perror("A signal occurred before child exited");
    exit(0);
}



