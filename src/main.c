#include <stdio.h>
#include "bistro.h"

int main(int argc, char **argv) {
    if (argc != 4)
        return 1;
    list_t expr = parse(my_strdup(argv[1]), argv[2], argv[3]);
    if (expr == NULL)
        return 1;
    number_t *result = eval(expr, argv[2]);
    if (result == NULL)
        return 1;
    print_number(result);
    free_number(result);
    return 0;
}
