#include <unistd.h>
#include "bistro.h"

int my_strcmp(char *a, char *b) {
    int i;

    for (i = 0; a[i] && b[i] && a[i] == b[i]; i++);
    if (a[i] == '\0' && b[i]  == '\0') {
        return 0;
    }
    return a[i] < b[i] ? -1 : 1;
}