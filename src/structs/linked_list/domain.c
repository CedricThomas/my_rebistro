#include "bistro.h"

void print_elem(elem_t *elem) {
    char operators[] = NORMALIZED_OPERATORS;
    if (elem->type == Operator) {
        my_putchar(operators[*((int *)elem->value)]);
        my_putchar('\n');
    } else {
        print_number(elem->value);
    }
}

static void print_list_elem(elem_t *elem) {
    char operators[] = NORMALIZED_OPERATORS;
    if (elem->prev != NULL) {
        my_putchar(' ');
    }
    if (elem->type == Operator) {
        my_putchar(operators[*((int *)elem->value)]);
    } else {
        if (((number_t *)(elem->value))->sign != Plus)
            my_putchar(((number_t *)(elem->value))->sign);
        my_putstr(((number_t *)(elem->value))->value);
    }
}

void print_list(list_t list) {
    apply_to_elems(list, &print_list_elem);
    my_putchar('\n');
}

void apply_to_elems(list_t list, void (*fct)(elem_t *)) {
    while (list) {
        fct(list);
        list = list->next;
    }
}

int get_elem_op(elem_t *elem) {
    int *operator = NULL;

    if (elem == NULL)
        return -1;
    if (elem->type != Operator)
        return -1;
    operator = elem->value;
    return *operator; 
}