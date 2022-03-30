#include <stdlib.h>
#include "bistro.h"

static char *search_and_sub(number_t *rest, number_t **table, char *result) {
    number_t *value;
    char *result_index;
    int i = -1;

    if (cmp_number_abs(rest, table[0]) <= 0)
        for (i = 0; i < 9 && cmp_number_abs(rest, table[i + 1]) <= 0; i++);
    if (i < 0)
        return my_strcat(result, "0");
    value = new_numberdup(Plus, table[i]->value);
    value = sub(new_numberdup(Plus, rest->value), value);
    result_index = inttostr(i + 1);
    if (result_index == NULL || value == NULL)
        return ERROR_PTR("Invalid division result allocation.", NULL);
    my_strcat(result, result_index);
    my_strcpy(rest->value, value->value);
    free(result_index);
    free_number(value);
    return result;
}

static char *divide_op_compute(char *number, number_t **table) {
    char *result = my_strdup(number);
    number_t *tmp = new_numberdup(Plus, number);
    
    if (tmp == NULL || result == NULL) {
        return ERROR_PTR("Invalid table allocation.", NULL);
    }
    my_memset(tmp->value, 0, my_strlen(number));
    my_memset(result, 0, my_strlen(number));
    while (*number) {
        my_strncat(tmp->value, number, 1);
        my_strnshift(number, 1);
        epurate_number(tmp);
        if (search_and_sub(tmp, table, result) == NULL)
            return NULL;
        epurate_number(tmp);
    }
    free_number(tmp);
    return result;
}

static number_t **get_table(number_t *a) {
    number_t **table = malloc(sizeof(number_t *) * 10);
    char *raw_incr = malloc(sizeof(char) * 3);
    number_t *cpy;
    number_t *incr;

    if (table == NULL)
        return NULL;
    my_memset(raw_incr, 0, sizeof(char) * 3);
    for (int i = 0; i < 10; i++) {
        raw_incr[0] = i == 9 ? '1' : '1' + i;
        raw_incr[1] = i < 9 ? '\0' : '0'; 
        cpy = new_numberdup(Plus, a->value);
        incr = new_numberdup(Plus, raw_incr);
        table[i] = multiply(cpy, incr);
        if (table[i] == NULL) {
            return NULL;
        }
    }
    free(raw_incr);
    return table;
}

static number_t *divide_op(number_t *a, number_t *b) {
    sign_e sign = get_multiply_divide_sign(a, b);
    char *result;
    char *cpy;
    number_t **table = NULL;

    if (my_strlen(b->value) == 1 && b->value[0] == '0')
        return ERROR_PTR("Cannot divide by 0.", NULL); 
    if (cmp_number_abs(a, b) > 0)
        return new_numberdup(sign, "0"); 
    if (cmp_number_abs(a, b) == 0)
        return new_numberdup(sign, "1"); 
    table = get_table(b);
    cpy = my_strdup(a->value);
    if (table == NULL || cpy == NULL)
        return ERROR_PTR("Invalid division resources allocation.", NULL);
    result = divide_op_compute(cpy, table);
    for (int i = 0; i < 10; i++)
        free_number(table[i]);
    free(table);
    free(cpy);
    return new_number(sign, result);
}

number_t *divide(number_t *a, number_t *b) {
    number_t *result;

    if (a == NULL || b == NULL)
        return NULL;
    result = divide_op(a, b);
    free_number(a);
    free_number(b);
    return result;
}
