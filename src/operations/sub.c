#include <stdlib.h>
#include "bistro.h"

static char *sub_op_compute(char *max, char *min) {
    int tmp;
    int i = 0;
    int j = 0;
    int carry = 0; 
    char *result = malloc(sizeof(char) * (my_strlen(max) + 1));
 
    if (result == NULL)
        return ERROR_PTR("Invalid sub allocation.", NULL);
    for (; max[i]; i++) {
        tmp = max[i] - '0' - carry;
        if (min[j]) {
            tmp -= min[j] - '0';
            j++;
        }
        result[i] = tmp + 10 * (tmp < 0) + '0';
        carry = tmp < 0 ? 1 : 0;
    }
    result[i] = '\0';
    return result;
}

number_t *sub_op(number_t *a, number_t *b) {
    int cmp_abs = cmp_number_abs(a, b);
    sign_e sign;
    char *result;

    my_revstr(a->value);
    my_revstr(b->value);
    if (cmp_abs < 0)
        result = sub_op_compute(a->value, b->value);
    else
        result = sub_op_compute(b->value, a->value);
    my_revstr(a->value);
    my_revstr(b->value);
    if (result == NULL)
        return NULL;
    my_revstr(result);
    sign = (cmp_abs > 0) ? get_inverse_sign(a->sign) : a->sign;
    return new_number(sign, result);
}

number_t *sub(number_t *a, number_t *b) {
    number_t *result;

    if (a == NULL || b == NULL)
        return NULL;
    result = select_operation_plus_minus(a, b, Sub);
    free_number(a);
    free_number(b);
    return result;
}
