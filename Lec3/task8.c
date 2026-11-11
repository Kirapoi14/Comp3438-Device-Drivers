#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char * cmd[] = {"/bin/ls", "-l", NULL};
int main(int argc, char * argv[]) {
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0600);
    close(STDOUT_FILENO);
    dup(fd);
    execvp(cmd[0], cmd);
    close(fd);
    return -1;
}