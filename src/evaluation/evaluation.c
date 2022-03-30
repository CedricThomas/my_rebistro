#include <stdlib.h>
#include "bistro.h"

static number_t *(* const unary[])(number_t *a) = {
    &unary_minus, // -
    &unary_plus, // +
};

static number_t *(* const dual[])(number_t *a, number_t *b) = {
    &add, // +
    &sub,  // -
    &multiply, // *
    &divide, // /
    &rest, // %
};

static void change_base(
    list_t l,
    char *base,
    number_t *(*f)(number_t *, char *)
) {
    while (l) {
        if (l->type == Number)
            l->value = f(l->value, base);
        l = l->next;
    }
}

static void execute_unary_operator(list_t list, op_e op) {
    list->prev->value = unary[op - FIRST_UNARY_OPERATOR](list->prev->value);
    list->prev->next = list->next;
    if (list->next)
        list->next->prev = list->prev;
    free(list->value);
    free(list);    
}

static void execute_dual_operator(list_t list, op_e op) {
    list_t prev = list->prev;
    void *a = prev->prev->value;
    void *b = prev->value;

    prev->prev->value = dual[op - FIRST_DUAL_OPERATOR](a, b);
    prev->prev->next = list->next;
    if (list->next)
        list->next->prev = prev->prev;
    free(list->value);
    free(list);
    free(prev);
}

static void exec_first_valid_op(list_t list) {
    op_e op;

    while (list->type != Operator)
        list = list->next;
    op = get_elem_op(list);
    if (op < FIRST_UNARY_OPERATOR)
        execute_dual_operator(list, op);
    else
        execute_unary_operator(list, op);
}

number_t *eval(list_t expr, char *base) {
    number_t *result = NULL;

    change_base(expr, base, convert_base_to_decimal);
    while (expr->next)
        exec_first_valid_op(expr);
    change_base(expr, base, convert_decimal_to_base);
    result = expr->value;
    expr->value = NULL;
    delete_list(&expr);
    return result;
}
