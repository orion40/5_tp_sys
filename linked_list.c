#include "linked_list.h"

void linked_list_init(struct linked_list_head *list) {
    list->head=NULL;
    init(&list->sync);
}

int linked_list_exists(struct linked_list_head *list, int val) {
    struct linked_list *p;
    begin_read(&list->sync);
    p=list->head;
    while(p) {
        if (p->nb == val) {
            end_read(&list->sync);
            return 1;
        }
        p=p->next;
    }
    end_read(&list->sync);
    return 0;
}

struct linked_list* linked_list_remove(struct linked_list_head *list, int val) {
    struct linked_list **p, *ret=NULL;
    begin_write(&list->sync);
    p=&list->head;
    while(*p) {
        if ((*p)->nb == val) {
            ret=*p;
            *p=(*p)->next;
            break;
        }
        p=&(*p)->next;
    }
    end_write(&list->sync);
    return ret;
}
