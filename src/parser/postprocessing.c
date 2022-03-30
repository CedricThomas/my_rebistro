#include "bistro.h"

static op_e get_unary_version(op_e op) {
    if (op == Sub) {
        return UMinus;
    } else if (op == Add) {
        return UPlus;
    } else {
        return op;
    }
}

static void unary_converter(elem_t *elem) {
    int *operator = NULL;
    int current_op = get_elem_op(elem);
    int next_op = get_elem_op(elem->next);
    int prev_op = get_elem_op(elem->prev);
    int has_prev = elem->prev != NULL;

    if (current_op < 0)
        return;
    operator = elem->value;
    if (!has_prev || prev_op >= 0)
        *operator = get_unary_version(*operator);
    if (next_op == OParent)
        *operator = get_unary_version(*operator);
}

list_t postprocess(list_t expr) {
    apply_to_elems(expr, &unary_converter);
    return expr;
}
