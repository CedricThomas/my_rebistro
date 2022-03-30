#include <unistd.h>

void my_putchar(char c) {
    write(1, &c, 1);
}

void my_putchard(int fd, char c) {
    write(fd, &c, 1);
}