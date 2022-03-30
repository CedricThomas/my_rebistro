#include <stdlib.h>
#include "bistro.h"

int *my_intndup(int *array, size_t size) {
    int *dup = malloc(sizeof(int) * (size + 1));

    if (dup == NULL)
        return NULL;
    for (size_t i = 0; i < size; i++) {
        dup[i] = array[i];
    }
    return dup;
}
