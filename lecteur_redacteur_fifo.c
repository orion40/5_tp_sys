#include "lecteur_redacteur_fifo.h"
#include <stdio.h>

// TODO : 
// se rapeller de ce qu'on a voulu faire
// faire les fonctions pour la liste

list_elem* linked_list_get_last_elem(struct head_s list_head){
    fprintf(stderr, "IMPLEMENT %s", __FUNCTION__);
}

list_elem* linked_list_depiler (struct head_s list_head){
    fprintf(stderr, "IMPLEMENT %s", __FUNCTION__);
}

void se_mettre_en_attente (lecteur_redacteur_t *lr, int est_lecteur){
    list_elem* last_elem;
    last_elem = linked_list_get_last_elem(lr->list_head);
    list_elem* new_element = (list_elem*) malloc(sizeof(list_elem));

    pthread_cond_t* signal = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    new_element->est_lecteur = est_lecteur;
    pthread_cond_init(&new_element->signal, NULL);
    STAILQ_INSERT_TAIL(&lr->list_head, new_element, next);
    pthread_cond_wait(&new_element->signal, &lr->mutex);

    pthread_cond_destroy(&new_element->signal);
    free(&new_element->signal);
    free(new_element);
}

void passer_la_main (lecteur_redacteur_t *lr){
    list_elem* first_elem;
    first_elem = STAILQ_FIRST(&lr->list_head); // LECTURE seulemement, pas POP
    if (!STAILQ_FIRST(&lr->list_head)->est_lecteur){
        pthread_cond_signal(&first_elem->signal);
        linked_list_depiler(lr->list_head);
    } else {
        while (first_elem->est_lecteur){
            pthread_cond_signal(&first_elem->signal);
            linked_list_depiler(lr->list_head);
            first_elem = STAILQ_FIRST(&lr->list_head);
        }
    }
}

/* fonction: initialiser_lecteur_redacteur
 * Permet d'initialiser les structures d'un lecteur_redacteur_t
 * correctement.
 * lr : le lecteur_redacteur_t à initialiser.
 */
void initialiser_lecteur_redacteur(lecteur_redacteur_t * lr){
    fprintf(stderr, "Priorité FIFO...\n");

    STAILQ_INIT(&lr->list_head);
    pthread_mutex_init(&lr->mutex, NULL);
}

/* fonction: detruire_lecteur_redacteur
 * Permet de libérer les structures internes d'un lecteur_redacteur_t.
 * lr : le lecteur_redacteur_t à libérer.
 */
void detruire_lecteur_redacteur(lecteur_redacteur_t * lr){
    pthread_mutex_destroy(&lr->mutex);
    list_elem * e = NULL;

    while (!STAILQ_EMPTY(&lr->list_head))
    {
        e = STAILQ_FIRST(&lr->list_head);
        pthread_cond_destroy(&e->signal);
        STAILQ_REMOVE(&lr->list_head, e, list_elem, next);
        free(e);
        e = NULL;
    }
}

/* fonction: debut_lecture
 * Indique le début d'une lecture.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    if (!STAILQ_EMPTY(&lr->list_head)){
        se_mettre_en_attente(lr, 1);
    }

    while (STAILQ_FIRST(&lr->list_head)->nb_redacteur){
        se_mettre_en_attente(lr, 1);
    }

    STAILQ_FIRST(&lr->list_head)->nb_lecteur++;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_lecture
 * Indique la fin d'une lecture.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    STAILQ_FIRST(&lr->list_head)->nb_lecteur--;

    if (STAILQ_FIRST(&lr->list_head)->nb_lecteur == 0){
        passer_la_main(lr);
    }

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: debut_redaction
 * Indique le début d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    // TODO : check if first is NULL
    if (!STAILQ_EMPTY(&lr->list_head)){
        while(STAILQ_FIRST(&lr->list_head)->nb_redacteur &&
                STAILQ_FIRST(&lr->list_head)->nb_lecteur > 0){
            se_mettre_en_attente(lr, 0);
        }
    }

    STAILQ_FIRST(&lr->list_head)->nb_redacteur = 1;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_redaction
 * Indique la fin d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    STAILQ_FIRST(&lr->list_head)->nb_redacteur = 0;

    passer_la_main(lr);

    pthread_mutex_unlock(&lr->mutex);
}
