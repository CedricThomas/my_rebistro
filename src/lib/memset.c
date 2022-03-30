#include <stddef.h>

void *my_memset(void *s, int c, size_t n) {
    unsigned char *data = s;

    for (size_t i = 0; i < n; i++)
        data[i] = (unsigned char)c; 
    return s;
}