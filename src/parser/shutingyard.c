#include <stdio.h>
#include "bistro.h"

//'()+-*/%'
static const int weights[9] = {
    0,  // (
    1, // )
    1,  // +
    1,  // -
    2,  // *
    2,  // /
    2,  // %
    3, // + 
    3  // -
};

static int handle_number(list_t *input, list_t *output, list_t *operators) {
    (void)operators;
    move_list_head(output, input);
    return 0;
}

static int handle_operator(list_t *in, list_t *output, list_t *ops) {
    while (*ops && weights[get_elem_op(*ops)] > weights[get_elem_op(*in)])
        move_list_head(output, ops);
    move_list_head(ops, in);
    return 0;
}

static int handle_closing_parent(list_t *input, list_t *output, list_t *ops) {
    op_e op = get_elem_op(*ops) ;
    
    while (op >= 0 && op != OParent) {
        move_list_head(output, ops);
        op = get_elem_op(*ops) ;
    }
    if ((*ops) == NULL) {
        return -1;
    } else {
        delete_list_head(input);
        delete_list_head(ops);
    }
    return 0;
}

static int handle_opening_parent(list_t *input, list_t *output, list_t *ops) {
    (void)output;
    move_list_head(ops, input);
    return 0;
}

static int (* const fct[9])(list_t *, list_t *, list_t *) = {
    &handle_opening_parent, // (
    &handle_closing_parent,  // )
    &handle_operator, // +
    &handle_operator, // -
    &handle_operator, // *
    &handle_operator, // /
    &handle_operator, // %
    &handle_operator, // -
    &handle_operator, // +
};

list_t shutingyard(list_t *input) {
    int error;
    list_t output = NULL;
    list_t operators = NULL;

    while (*input) {
        if ((*input)->type == Operator)
            error = fct[get_elem_op(*input)](input, &output, &operators);
        else
            error = handle_number(input, &output, &operators);
        if (error == -1) {
            return ERROR_PTR("Syntax error.", NULL);
        }
    }
    while (operators)
        move_list_head(&output, &operators);
    rev_list(&output);
    return output;
}
