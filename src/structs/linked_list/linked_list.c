#include <stdlib.h>
#include "bistro.h"

list_t append_elem(list_t *list, int type, void *value) {
    elem_t *elem = malloc(sizeof(elem_t));
    elem_t *tmp = *list;

    if (elem == NULL || value == NULL)
        return ERROR_PTR("Invalid element allocation.", 0);
    elem->type = type;
    elem->value = value;
    elem->next = NULL;
    elem->prev = NULL;
    if (*list == NULL) {
        *list = elem;
    } else {
        while (tmp && tmp->next)
            tmp = tmp->next;
        tmp->next = elem;
        elem->prev = tmp;
    }
    return elem;
}

void move_list_head(list_t *dest, list_t *src) {
    list_t tmpdest = *dest; 
    list_t tmpsrc = *src; 
    list_t srcnext; 
    
    if (!tmpsrc)
        return;
    srcnext = tmpsrc->next;
    tmpsrc->next = tmpdest;
    if (tmpdest)
        tmpdest->prev = tmpsrc;
    if (srcnext)
        srcnext->prev = NULL;
    *dest = *src;
    *src = srcnext;    
}

void delete_list_head(list_t *a) {
    list_t tmp = *a; 

    if (!tmp)
        return;
    *a = tmp->next;
    if (tmp->next) {
        tmp->next->prev = NULL;
    }
    free(tmp->value);
    free(tmp);
}

void rev_list(list_t *list) {
    list_t tmp = *list;
    list_t new = NULL;

    if (!tmp)
        return;
    while (tmp) {
        move_list_head(&new, &tmp);
    }
    *list = new;
}

void delete_list(list_t *list) {
    while (*list) {
        delete_list_head(list);
    }
}