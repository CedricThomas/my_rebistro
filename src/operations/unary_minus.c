#include "bistro.h"

number_t *unary_minus(number_t *a) {
    a->sign = get_inverse_sign(a->sign);
    return a;
}