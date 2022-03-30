#include <stdlib.h>
#include "bistro.h"

number_t *new_number(sign_e sign, char *value) {
    number_t *number = malloc(sizeof(number_t));

    if (number == NULL || value == NULL) {
        return ERROR_PTR("Invalid allocation.", NULL);
    }
    number->sign = sign;
    number->value = value;
    epurate_number(number);
    return number;
}

number_t *new_numberdup(sign_e sign, char *value) {
    number_t *number = malloc(sizeof(number_t));

    if (number == NULL || value == NULL) {
        return ERROR_PTR("Invalid allocation.", NULL);
    }
    number->sign = sign;
    number->value = my_strdup(value);
    if (number->value == NULL) {
        return ERROR_PTR("Invalid allocation.", NULL);
    }
    epurate_number(number);
    return number;
}

void free_number(number_t *number) {
    if (number != NULL) {
        free(number->value);
        free(number);
    }
}

void print_number(number_t *number) {
    if (number == NULL) {
        ERROR_PTR("Invalid number printing.", 0);
        return;
    }
    if (number->sign != Plus) {
        my_putchar(number->sign);
    }
    my_putstr(number->value);
    my_putchar('\n');
}
