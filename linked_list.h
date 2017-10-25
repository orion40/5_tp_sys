#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "lecteur_redacteur_fifo.h"

struct linked_list {
    int nb;
    struct linked_list *next;
};

struct linked_list_head {
    lecteur_redacteur_t sync;
    struct linked_list *head;
};

void linked_list_init(struct linked_list_head *list);
int linked_list_exists(struct linked_list_head *list, int val);
struct linked_list* linked_list_remove(struct linked_list_head *list, int val);

#endif
