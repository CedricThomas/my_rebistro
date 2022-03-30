#include <stdlib.h>
#include "bistro.h"

static int append_number(list_t *list, char **expr, const char *base)
{
    int index = my_strlen_in(*expr, base);
    void *value = new_number(Plus, my_strndup(*expr, index));
    int type = Number;
    
    (*expr) += index;
    if (append_elem(list, type, value) == NULL)
        return 1;
    return 0;
}

static int append_operator(list_t *list, char **expr, const char *ops)
{
    int index = index_of(**expr, ops);
    void *value = my_intndup(&index, 1);
    int type = Operator;
    
    (*expr)++;
    if (append_elem(list, type, value) == NULL)
        return 1;
    return 0;
}

static int skip_trash(list_t *list, char **expr, const char *dict)
{
    int index = my_strlen_in(*expr, dict);

    (*expr) += index;
    (void)list;
    return 0;
}

static list_t analyse(char *expr, char *base, char *operators) {
    list_t tokens = NULL;
    int i;
    int (*fct[])(list_t *, char **, const char *) = {
        &append_number, &append_operator, &skip_trash
    };
    const char *dicts[] = {
        base, operators, "\t ",
    };

    while (*expr) {
        for (i = 0; index_of(*expr, dicts[i]) < 0; i++);
        if (fct[i](&tokens, &expr, dicts[i]) != 0) {
            delete_list(&tokens);
            return ERROR_PTR("Can't analyse expression", NULL);
        }
    }
    return tokens;
}

list_t parse(char *expr, char *base, char *operators) {
    list_t tokens;

    expr = preprocess(expr, base, operators);
    if (expr == NULL)
        return NULL;
    tokens = analyse(expr, base, operators);
    free(expr);
    if (tokens == NULL)
        return NULL;
    tokens = postprocess(tokens);
    if (tokens == NULL)
        return NULL;
    tokens = shutingyard(&tokens);
    return tokens;
}