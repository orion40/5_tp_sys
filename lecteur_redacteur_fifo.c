#include "lecteur_redacteur_fifo.h"
#include <stdio.h>

// TODO : 
// se rapeller de ce qu'on a voulu faire
// faire les fonctions pour la liste
//

void se_mettre_en_attente (list_elem* liste_attente, int est_lecteur){
    list_elem* last_elem;
    last_elem = linked_list_get_last_elem (liste_attente);
    struct list_elem* new_element = malloc(sizeof(list_elem));

    pthread_cond_t* signal = malloc(sizeof(pthread_cond_t));
    new_element->est_lecteur = est_lecteur;
    pthread_cond_init(new_element, NULL);
    last_elem->next = new_element;
    pthread_cond_wait(new_element->signal, lr->mutex);

    pthread_cond_destroy(new_element->signal);
    free(new_element->signal);
    free(new_element);
}

void passer_la_main (list_elem* liste_attente){
    list_elem* first_elem;
    first_elem = linked_list_get_first_elem(liste_attente); // LECTURE seulemement, pas POP
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

list_elem* linked_list_depiler (list_elem *list){

}

/* fonction: initialiser_lecteur_redacteur
 * Permet d'initialiser les structures d'un lecteur_redacteur_t
 * correctement.
 * lr : le lecteur_redacteur_t à initialiser.
 */
void initialiser_lecteur_redacteur(lecteur_redacteur_t * lr){
    fprintf(stderr, "Priorité FIFO...\n");
    lr->nb_redacteur = 0;
    lr->nb_lecteur = 0;

    pthread_mutex_init(&lr->mutex, NULL);
    pthread_cond_init(&lr->signal, NULL);
}

/* fonction: detruire_lecteur_redacteur
 * Permet de libérer les structures internes d'un lecteur_redacteur_t.
 * lr : le lecteur_redacteur_t à libérer.
 */
void detruire_lecteur_redacteur(lecteur_redacteur_t * lr){
    pthread_mutex_destroy(&lr->mutex);
    pthread_cond_destroy(&lr->signal);
}

/* fonction: debut_lecture
 * Indique le début d'une lecture.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    if (! linked_list_is_empty(liste_attente)){
        se_mettre_en_attente(lr->list, 1);
    }

    while (lr->nb_redacteur){
        se_mettre_en_attente(lr->list, 1);
    }

    lr->nb_lecteur++;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_lecture
 * Indique la fin d'une lecture.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    lr->nb_lecteur--;

    if (lr->nb_lecteur == 0){
        passer_la_main(lr->list);
    }

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: debut_redaction
 * Indique le début d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    while(lr->nb_redacteur && lr->nb_lecteur > 0){
        se_mettre_en_attente(lr->list, 0);
    }

    lr->nb_redacteur = 1;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_redaction
 * Indique la fin d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    lr->nb_redacteur = 0;

    passer_la_main(lr->list);

    pthread_mutex_unlock(&lr->mutex);
}
