#include <stdlib.h>
#include "bistro.h"

static void multiply_single_digit(char* result, char *number, int digit) {
    int i = 0;
    int tmp;
    int carry = 0;

    for (; number[i]; i++) {
        tmp = (number[i] - '0') * digit + carry;
        result[i] = (tmp % 10) + '0';
        carry = tmp / 10;
    }
    result[i] = carry ? (carry + '0') : '\0';
    result[i + 1] = '\0';
}

static number_t **get_multiplication_stack(number_t *a, number_t *b) {
    int blen = my_strlen(b->value);
    int max_len = blen + my_strlen(a->value);
    number_t **stack = malloc(sizeof(number_t *) * (blen + 1));

    if (stack == NULL)
        return ERROR_PTR("Invalid stack allocation.", NULL);
    stack[blen] = NULL;
    for (int i = 0; i < blen; i++) {
        stack[i] = malloc(sizeof(number_t));
        if (stack[i] == NULL)
            return ERROR_PTR("Invalid multiply allocation.", NULL);
        stack[i]->value = malloc(sizeof(char) * (max_len + 1));
        stack[i]->sign = Plus;
        if (stack[i]->value == NULL)
            return ERROR_PTR("Invalid multiply  allocation.", NULL);
        my_memset(stack[i]->value, '0', max_len);
        multiply_single_digit(stack[i]->value + i, a->value, b->value[i] - '0');
        my_revstr(stack[i]->value);
    }
    return stack;
}

static number_t *compute_multiplication_stack(number_t **stack) {
    number_t *acc = stack[0];

    for (int i = 1; stack[i] != NULL; i++) {
        acc = add(acc, stack[i]);
    }
    free(stack);
    return acc;
}

static number_t *multiply_op(number_t *a, number_t *b) {
    sign_e sign = get_multiply_divide_sign(a, b);
    number_t **stack;
    number_t *result;

    my_revstr(a->value);
    my_revstr(b->value);
    stack = get_multiplication_stack(a, b);
    if (stack == NULL)
        return NULL;
    result = compute_multiplication_stack(stack);
    my_revstr(a->value);
    my_revstr(b->value);
    if (result == NULL)
        return NULL;
    result->sign = sign;
    return result;
}

number_t *multiply(number_t *a, number_t *b) {
    number_t *result;

    if (a == NULL || b == NULL)
        return NULL;
    result = multiply_op(a, b);
    free_number(a);
    free_number(b);
    return result;
}
