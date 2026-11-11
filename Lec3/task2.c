#include <unistd.h>
#include <stdio.h>

int main() {
    char buf[1024]; // char[1024], char *
    char *buf1 = buf;
    printf("size of buf is %ld.\n", sizeof(buf));
    printf("size of buf is %ld.\n", sizeof(buf1));
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("failed to get the cwd.");
        return -1;
    }
    printf("the current working directory is %s.\n", buf);
    return 0;
}