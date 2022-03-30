#include <stdlib.h>
#include "bistro.h"

static number_t *rest_op(number_t *a, number_t *b) {
    number_t *adup = new_numberdup(Plus, a->value);
    number_t *bdup = new_numberdup(Plus, b->value);
    number_t *result;
    

    if (my_strlen(b->value) == 1 && b->value[0] == '0')
        return ERROR_PTR("Cannot modulo by 0.", NULL); 
    result = divide(adup, bdup);
    result = multiply(result, new_numberdup(Plus, b->value));
    result = sub(new_numberdup(Plus, a->value), result);
    result->sign = a->sign;
    return result;
}

number_t *rest(number_t *a, number_t *b) {
    number_t *result;

    if (a == NULL || b == NULL)
        return NULL;
    result = rest_op(a, b);
    free_number(a);
    free_number(b);
    return result;
}
