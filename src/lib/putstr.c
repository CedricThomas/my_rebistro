#include <unistd.h>
#include "bistro.h"

void my_putstr(char *str) {
    int len = my_strlen(str);

    write(1, str, len);
}