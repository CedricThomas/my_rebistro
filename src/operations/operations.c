#include "bistro.h"

number_t *add_op(number_t *a, number_t *b);
number_t *sub_op(number_t *a, number_t *b);
/*
- - - => SUB
+ - + => SUB
+ + - => SUB
- + + => SUB
+ + + => ADD
- + - => ADD
+ - - => ADD
- - + => ADD
IF RIGHT > LEFT, INVERSE LEFT SIGN ELSE LEFT SIGN 
*/

number_t *select_operation_plus_minus(number_t *a, number_t *b, op_e operation) {
    if (((a->sign == Minus) + (b->sign == Minus)) % 2 == 0) {
        if (operation == Add)
            return add_op(a, b);
        else
            return sub_op(a, b);
    } else {
        if (operation == Add)
            return sub_op(a, b);
        else
            return add_op(a, b);
    }
}

sign_e get_multiply_divide_sign(number_t *a, number_t *b) {
    if (((a->sign == Minus) + (b->sign == Minus)) % 2 == 0) {
        return Plus;
    } else {
        return Minus;
    }

}