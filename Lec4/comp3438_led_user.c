#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
    int fd;
    fd = open(argv[1], O_WRONLY);
    if (fd < 0) {
        perror("Cannot open the device file.");
        return -1;
    }

    int cnt = write(fd, argv[2], 1);
    printf("Content written into %s is %c.\n", argv[1], argv[2][0]);
    close(fd);
}