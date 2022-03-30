#include <stdlib.h>
#include "bistro.h"

static number_t *get_base_index(char c, char *base) {
    int i = index_of(c, base);
    
    if (i < 0)
        return NULL;
    return new_number(Plus, inttostr(i));
}

static number_t *compute(number_t *num, char *bdest, number_t *res, int depth) {
    char *blen = inttostr(my_strlen(bdest));
    number_t *null = new_numberdup(Plus, "0");
    number_t *numdup = new_numberdup(Plus, num->value);
    number_t *mod = rest(numdup, new_numberdup(Plus, blen));
    number_t *divided = divide(num, new_number(Plus, blen));

    if (mod == NULL || divided == NULL || null == NULL)
            return ERROR_PTR("Invalid allocation", NULL); 
    if (cmp_number_abs(divided, null) != 0) {
        res = compute(divided, bdest, res, depth + 1);
        res->value[depth] = bdest[my_getnbr(mod->value)];
    } else {
        if ((res->value = malloc(sizeof(char) * (depth + 2))) == NULL)
            return ERROR_PTR("Invalid allocation", NULL); 
        res->value[depth + 1] = '\0';
        res->value[depth] = bdest[my_getnbr(mod->value)];
        free_number(divided);
    }
    free_number(null);
    free_number(mod);
    return res;
}

number_t *convert_decimal_to_base(number_t *number, char *dest) {
    number_t *res = malloc(sizeof(number_t));

    if (res == NULL)
        return ERROR_PTR("Invalid allocation", NULL); 
    res->sign = number->sign;
    number->sign = Plus;
    res = compute(number, dest, res, 0);
    my_revstr(res->value);
    return  res;
}

number_t *convert_base_to_decimal(number_t *number, char *source) {
    number_t *index;
    number_t *converted = new_numberdup(Plus, "0");
    char *base_lenght = inttostr(my_strlen(source));

    if (base_lenght == NULL || number == NULL)
        return ERROR_PTR("Invalid allocation.", NULL);
    for (int i = 0; number->value[i] != '\0'; i++) {
        index = get_base_index(number->value[i], source);
        if (index == NULL)
            return ERROR_PTR("Invalid convertion index.", NULL);
        converted = multiply(converted, new_numberdup(Plus, base_lenght));
        converted = add(converted, index);
    }
    if (converted == NULL)
        return ERROR_PTR("Invalid convertion.", NULL);
    converted->sign = number->sign;
    free(base_lenght);
    free_number(number);
    return converted;
}
