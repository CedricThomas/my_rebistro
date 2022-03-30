#pragma once

#include <stddef.h>

#define ERROR_INT(error, code) my_puterrord(error, __LINE__, __FILE__, code)
#define ERROR_PTR(error, ptr) my_puterrorp(error, __LINE__, __FILE__, ptr)
#define OPERATORS_DICT_LENGHT 7
#define FIRST_UNARY_OPERATOR 7
#define FIRST_DUAL_OPERATOR 2
#define NORMALIZED_OPERATORS "()+-*/%-+"

typedef struct elem_s {
    int type;
    void *value;
    struct elem_s *prev;
    struct elem_s *next;
} elem_t;

typedef elem_t *list_t;

typedef enum {
    Minus = '-',
    Plus = '+'
} sign_e;

typedef enum {
    OParent = 0,
    CParent = 1,
    Add = 2,
    Sub = 3,
    Multiply = 4,
    Divide = 5,
    Rest = 6,
    UMinus = 7,
    UPlus = 8,
} op_e;

typedef enum {
    Operator = 0,
    Number = 1,
} type_e;

typedef struct {
    sign_e sign;
    char *value;
} number_t;

// lib
char *my_strndup(char *str, unsigned int size);
char *my_strdup(char *str);

int *my_intndup(int *array, size_t size);

int my_strlen(const char *str);
int my_strlen_in(const char *str, const char *alphabet);

int my_puterrord(char *error, int line, char *file, int code);
void *my_puterrorp(char *error, int line, char *file, void *ptr);
void my_putstr(char *str);

void my_revstr(char *str);

int index_of(char needle, const char *haystack);

void putnbr(int nbr);
void putnbrd(int fd, int nbr);

void my_putchar(char c);
void my_putchard(int fd, char c);

int my_strcmp(char *a, char *b);

void *my_memset(void *s, int c, size_t n);

char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t n);

char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t n);

char *my_strnshift(char *str, size_t n);

char *inttostr(int number);

char *epurstr(char *str, char *dict);

int my_getnbr(char *str);

// operations
number_t *select_operation_plus_minus(number_t *a, number_t *b, op_e operation);
sign_e get_multiply_divide_sign(number_t *a, number_t *b);
number_t *add(number_t *a, number_t *b);
number_t *sub(number_t *a, number_t *b);
number_t *multiply(number_t *a, number_t *b);
number_t *divide(number_t *a, number_t *b);
number_t *rest(number_t *a, number_t *b);
number_t *unary_plus(number_t *a);
number_t *unary_minus(number_t *a);
number_t *convert_decimal_to_base(number_t *number, char *dest);
number_t *convert_base_to_decimal(number_t *number, char *source);

// base manipulation
number_t *convert_base(number_t *number, char *source, char *dest);

// parsing
list_t parse(char *expr, char *base, char *operators_dict);
char *preprocess(char *expr, char *base, char *ops);
list_t postprocess(list_t expr);
list_t shutingyard(list_t *expr);

// evaluation
number_t *eval(list_t expr, char *base);

// numbers
number_t *new_number(sign_e sign, char *value);
number_t *new_numberdup(sign_e sign, char *value);
int cmp_number_abs(number_t *a, number_t *b);
sign_e get_inverse_sign(sign_e sign);
void free_number(number_t *number);
void print_number(number_t *number);
void epurate_number(number_t *a);

// lists
list_t append_elem(list_t *list, int type, void *value);
void apply_to_elems(list_t list, void (*fct)(elem_t *));
void move_list_head(list_t *dest, list_t *src);
void delete_list_head(list_t *a);
void delete_list(list_t *list);
void rev_list(list_t *list);

void print_list(list_t list);
void print_elem(elem_t *elem);
int get_elem_op(elem_t *elem);