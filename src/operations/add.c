#include <stdlib.h>
#include "bistro.h"

static char *add_op_compute(char *max, char *min) {
    int tmp;
    int i = 0;
    int j = 0;
    int carry = 0; 
    char *result = malloc(sizeof(char) * (my_strlen(max) + 2));
 
    if (result == NULL)
        return ERROR_PTR("Invalid add allocation.", NULL);
    for (; max[i]; i++) {
        tmp = max[i] - '0';
        if (min[j]) {
            tmp += min[j] - '0';
            j++;
        }
        result[i] = (tmp % 10) + '0' + carry;
        carry = tmp / 10;
    }
    result[i] = carry ? '1' : '\0';
    result[i + 1] = '\0';
    return result;
}

number_t *add_op(number_t *a, number_t *b) {
    int cmp_result = cmp_number_abs(a, b);
    char *result;

    my_revstr(a->value);
    my_revstr(b->value);
    if (cmp_result < 0)
        result = add_op_compute(a->value, b->value);
    else
        result = add_op_compute(b->value, a->value);
    my_revstr(a->value);
    my_revstr(b->value);
    if (result == NULL)
        return NULL;
    my_revstr(result);
    return new_number(a->sign, result);
}

number_t *add(number_t *a, number_t *b) {
    number_t *result;

    if (a == NULL || b == NULL)
        return NULL;
    result = select_operation_plus_minus(a, b, Add);
    free_number(a);
    free_number(b);
    return result;
}