#include "bistro.h"

// IF A > B -> 1
// IF A < B -> -1
// IF A == B -> 0
inline int cmp_number_abs(number_t *a, number_t *b) {
    int lena = my_strlen(a->value);
    int lenb = my_strlen(b->value);

    if (lenb != lena)
        return lena < lenb ? 1 : -1;
    return my_strcmp(b->value, a->value);
}

sign_e get_inverse_sign(sign_e sign) {
    return sign == Plus ? Minus : Plus; 
}

void epurate_number(number_t *a) {
    int len = my_strlen(a->value);
    int i;

    for (i = 0; i < len - 1 && a->value[i] == '0'; i++);
    my_revstr(a->value);
    a->value[len - i] = '\0';
    my_revstr(a->value);
    if (my_strlen(a->value) == 1 && a->value[0] == '0') {
        a->sign = '+';
    }
}
