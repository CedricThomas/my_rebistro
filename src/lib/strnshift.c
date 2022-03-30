#include "bistro.h"

char *my_strnshift(char *str, size_t n) {
    int i = 0;
    int len;

    if (str == NULL)
        return NULL;
    len = my_strlen(str);
    for (int j = n; j < len && str[j]; j++) {
        str[i] = str[j];
        i++; 
    }
    str[i] = '\0';
    return str;
}