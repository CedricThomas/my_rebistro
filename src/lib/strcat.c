#include "bistro.h"

char *my_strncat(char *dest, const char *src, size_t n) {
    size_t i = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    for (; dest[i]; i++);
    for (size_t j = 0; j < n && src[j]; j++) {
        dest[i] = src[j];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, const char *src) {
    if (dest == NULL || src == NULL)
        return NULL;
    return my_strncat(dest, src, my_strlen(src));
}
