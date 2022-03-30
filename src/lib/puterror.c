#include <unistd.h>
#include "bistro.h"

int my_puterrord(char *error, int line, char *file, int code) {
    int errorlen = my_strlen(error);
    int filelen = my_strlen(file);

    write(2, "Error: ", 7);
    write(2, error, errorlen);
    write(2, "\n line: ", 8);
    putnbrd(2, line);
    write(2, "\n file: ", 8);
    write(2, file, filelen);
    write(2, "\n", 1);

    return code;
}

void *my_puterrorp(char *error, int line, char *file, void *ptr) {
    (void)(my_puterrord(error, line, file, 0));
    return ptr;
}