#include "linked_list.h"

// TODO:
// Cas ou on passe la main a un rédacteur, on en lit 1
// Cas ou on passe la main a un lecteur, on lit jusqu'au prochain
// redacteur ou NULL

struct list_elem {
 int est_lecteur;
 pthread_t_cond* signal;
}

void se_mettre_en_attente (int est_lecteur){
    last_elem = get_last_elem (liste_attente);
    struct list_elem* new_element = malloc(sizeof(list_elem));
    pthread_t_cond* signal = malloc(sizeof(pthread_t_cond));
    new_element->est_lecteur = est_lecteur;
    pthread_t_cond_init(new_element, NULL);
    last_elem->next = new_element;
    pthread_cond_wait(new_element->signal, global_mutex);

    pthread_cond_destroy(new_element->signal);
    free(new_element->signal);
    free(new_element);
}

// on a fini notre travail
void passer_la_main (){
    first_elem = get_first_elem(liste_attente); // LECTURE seulemement, pas POP
    if (!first_elem->est_lecteur){
        pthread_cond_signal(first_elem->signal);
        depiler(liste_attente);
    } else {
        while (first_elem->est_lecteur){
            pthread_cond_signal(first_elem->signal);
            depiler(liste_attente);
            first = first_elem->next;
        }
    }
}

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
