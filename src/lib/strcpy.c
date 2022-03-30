#include "bistro.h"

char *my_strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    for (; i < n && src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0'; 
    return dest;
}

char *my_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL)
        return NULL;
    return my_strncpy(dest, src, my_strlen(src));
}