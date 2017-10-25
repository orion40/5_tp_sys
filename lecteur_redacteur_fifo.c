#include "lecteur_redacteur_fifo.h"
#include "linked_list.h"
#include <stdio.h>

/* fonction: initialiser_lecteur_redacteur
 * Permet d'initialiser les structures d'un lecteur_redacteur_t
 * correctement.
 * lr : le lecteur_redacteur_t à initialiser.
 */
void initialiser_lecteur_redacteur(lecteur_redacteur_t * lr){
    fprintf(stderr, "Priorité FIFO...\n");
    lr->nb_redacteur_actif = 0;
    lr->nb_lecteur_actif = 0;
    lr->nb_lecteur_attente = 0;

    pthread_mutex_init(&lr->mutex, NULL);
    pthread_cond_init(&lr->notif_ecrivain, NULL);
    pthread_cond_init(&lr->notif_lecteur, NULL);
}

/* fonction: detruire_lecteur_redacteur
 * Permet de libérer les structures internes d'un lecteur_redacteur_t.
 * lr : le lecteur_redacteur_t à libérer.
 */
void detruire_lecteur_redacteur(lecteur_redacteur_t * lr){
    pthread_mutex_destroy(&lr->mutex);
    pthread_cond_destroy(&lr->notif_lecteur);
    pthread_cond_destroy(&lr->notif_ecrivain);
}

/* fonction: debut_lecture
 * Indique le début d'une lecture.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);
    lr->nb_lecteur_attente++;

    while (lr->nb_redacteur_actif > 0){
        pthread_cond_wait(&lr->notif_lecteur, &lr->mutex);
    }

    lr->nb_lecteur_actif++;
    lr->nb_lecteur_attente--;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_lecture
 * Indique la fin d'une lecture.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    lr->nb_lecteur_actif--;

    if (lr->nb_lecteur_actif == 0){
        pthread_cond_signal(&lr->notif_ecrivain);
    }

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: debut_redaction
 * Indique le début d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    while(lr->nb_redacteur_actif > 0 || lr->nb_lecteur_actif > 0){
        pthread_cond_wait(&lr->notif_ecrivain, &lr->mutex);
    }

    lr->nb_redacteur_actif++;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_redaction
 * Indique la fin d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    lr->nb_redacteur_actif--;

    if (lr->nb_lecteur_attente > 0){
        pthread_cond_broadcast(&lr->notif_lecteur);
    } else {
        pthread_cond_signal(&lr->notif_ecrivain);
    }

    pthread_mutex_unlock(&lr->mutex);
}
