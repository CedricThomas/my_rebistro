#include <stdlib.h>
#include "bistro.h"

static int count_digits(int number) {
    int i = number < 0;

    while (number != 0) {
        number /= 10;
        i++;
    }
    return i;
}

char *inttostr(int number) {
    int len = count_digits(number);
    int sign = number < 0;
    int i = 0;
    char *str;

    if (number == 0)
        return my_strdup("0");
    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    while (number != 0) {
        str[i] = (number % 10) + '0'; 
        number /= 10;
        i++;
    }
    if (sign)
        str[i] = '-';
    str[len] = '\0';
    my_revstr(str);
    return str;
}