#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char * const argv[]) {
    
    int fd;
    
    fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0) {
        perror("open file failure.");
        return -1;
    }

    const char * buf = "\nI will be back next week.";
    size_t intended = strlen(buf);

    size_t cnt;
    do {
        cnt = write(fd, buf, intended);
        if (cnt < 0) {
            perror("write failed.");
            return -1;
        }
        buf += cnt;
        intended -= cnt;
    } while (intended > 0);

    fsync(fd);
    close(fd);
}