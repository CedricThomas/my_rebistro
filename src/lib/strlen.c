#include "bistro.h"

int my_strlen(const char *str) {
    int i = -1;
    
    while (str[++i]);
    return i; 
}

int my_strlen_in(const char *str, const char *alphabet) {
    int i = -1;

    while (str[++i] && index_of(str[i], alphabet) >= 0);
    return i; 
}