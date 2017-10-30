#ifndef LECTEUR_REDACTEUR_FIFO_H
#define LECTEUR_REDACTEUR_FIFO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/queue.h>

struct HEADNAME *headp;

// TODO: besoin d'un type différent pour la tête de liste ?
typedef struct {
    struct list_elem *next;
    pthread_cond_t signal;
    int nb_redacteur;
    int nb_lecteur;
    int est_lecteur;
} list_elem;

typedef struct {
    SLIST_HEAD(HEADNAME, list_elem) list;
    pthread_mutex_t mutex;
} lecteur_redacteur_t;

void initialiser_lecteur_redacteur(lecteur_redacteur_t *);
void detruire_lecteur_redacteur(lecteur_redacteur_t *);
void debut_lecture(lecteur_redacteur_t *);
void fin_lecture(lecteur_redacteur_t *);
void debut_redaction(lecteur_redacteur_t *);
void fin_redaction(lecteur_redacteur_t *);

bool linked_list_is_empty(list_elem *list);
void linked_list_init(list_elem *list);
list_elem* linked_list_get_last_elem (list_elem *list);
list_elem* linked_list_get_first_elem (list_elem *list);
list_elem* linked_list_depiler (list_elem *list);

#endif
