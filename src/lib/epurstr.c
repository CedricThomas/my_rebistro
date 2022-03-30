#include <stdlib.h>
#include "bistro.h"

char *epurstr(char *str, char *dict) {
    char *dup;
    int len = 0;

    for (int i = 0; str[i]; i++)
        if (index_of(str[i], dict) < 0)
            len += 1;
    dup = malloc(sizeof(char) * (len + 1));
    if (dup == NULL)
        return NULL;
    len = 0;
    for (int i = 0; str[i]; i++) {
        if (index_of(str[i], dict) < 0) {
            dup[len] = str[i];
            len++;
        }
    }
    dup[len] = '\0';
    return dup;
}
