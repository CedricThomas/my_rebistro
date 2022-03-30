#include "bistro.h"

void my_revstr(char *str) {
    int len = my_strlen(str);
    char c;

    for (int i = 0; i < len / 2; i++) {
        c = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = c;
    }
}