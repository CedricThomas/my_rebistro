#include <stdlib.h>
#include "bistro.h"

// allocate a new expr without space for the children
char *preprocess(char *expr, char *base, char *ops) {
    char *new_expr = epurstr(expr, " \t");

    if (new_expr == NULL)
        return ERROR_PTR("Invalid expression allocation.", NULL);
    if (my_strlen(ops) != OPERATORS_DICT_LENGHT)
        return ERROR_PTR("Invalid operators dictionnary.", NULL);
    if (my_strlen(base) == 0)
        return ERROR_PTR("Invalid base dictionnary.", NULL);
    for (int i = 0; base[i]; i++)
        if (index_of(base[i], ops) >= 0)
            return ERROR_PTR("An operator is in the base.", NULL);
    for (int i = 0; new_expr[i]; i++)
        if (index_of(new_expr[i], base) < 0 && index_of(new_expr[i], ops) < 0)
            return ERROR_PTR("Invalid char in the expression.", NULL);
    free(new_expr);
    return expr; 
}
