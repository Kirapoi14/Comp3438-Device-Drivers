#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, const char * const argv[]) {
    
    int fd;

    fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        perror("open file failure.");
        return -1;
    }
    
    char buf[1024];
    int cnt;
    do {
        cnt = read(fd, buf, sizeof(buf) - 1);
        if (cnt < 0) {
            perror("read failed.");
            return -1;
        }
        buf[cnt] = 0;
        printf("%s", buf);
    } while (cnt > 0);
    printf("\n");
    
    close(fd);

}