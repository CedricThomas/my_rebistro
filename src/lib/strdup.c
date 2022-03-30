#include <stdlib.h>
#include "bistro.h"

char *my_strndup(char *str, unsigned int size) {
    char *dup = malloc(sizeof(char) * (size + 1));

    if (dup == NULL)
        return NULL;
    for (size_t i = 0; i < size; i++) {
        dup[i] = str[i];
    }
    dup[size] = '\0';
    return dup;
}

char *my_strdup(char *str) {
    return my_strndup(str, my_strlen(str));
}
