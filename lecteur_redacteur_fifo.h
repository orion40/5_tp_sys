#ifndef LECTEUR_REDACTEUR_FIFO_H
#define LECTEUR_REDACTEUR_FIFO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/queue.h>

struct HEADNAME *headp;

// TODO: besoin d'un type différent pour la tête de liste ?
struct list_elem {
    STAILQ_ENTRY(list_elem) next;
    pthread_cond_t signal;
    int est_lecteur;
};
typedef struct list_elem list_elem;

typedef struct {
    STAILQ_HEAD(head_s, list_elem) list_head;
    pthread_mutex_t mutex;
    int nb_redacteur;
    int nb_lecteur;
} lecteur_redacteur_t;

void initialiser_lecteur_redacteur(lecteur_redacteur_t *);
void detruire_lecteur_redacteur(lecteur_redacteur_t *);
void debut_lecture(lecteur_redacteur_t *);
void fin_lecture(lecteur_redacteur_t *);
void debut_redaction(lecteur_redacteur_t *);
void fin_redaction(lecteur_redacteur_t *);

#endif
