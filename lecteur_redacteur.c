#include "lecteur_redacteur.h"

void initialiser_lecteur_redacteur(lecteur_redacteur_t * lr){
    lr->nb_redacteur_actif = 0;
    lr->nb_lecteur_actif = 0;
    lr->nb_lecteur_attente = 0;

    pthread_mutex_init(&lr->mutex, NULL);
    pthread_cond_init(&lr->notif_ecrivain, NULL);
    pthread_cond_init(&lr->notif_lecteur, NULL);
}

void detruire_lecteur_redacteur(lecteur_redacteur_t * lr){
    pthread_mutex_destroy(&lr->mutex);
    pthread_cond_destroy(&lr->notif_lecteur);
    pthread_cond_destroy(&lr->notif_ecrivain);
}

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

void fin_lecture(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    lr->nb_lecteur_actif--;

    if (lr->nb_lecteur_actif == 0){
        pthread_cond_wait(&lr->notif_ecrivain, &lr->mutex);
    }

    pthread_mutex_unlock(&lr->mutex);
}

void debut_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    while(lr->nb_redacteur_actif > 0 || lr->nb_lecteur_actif > 0){
        pthread_cond_wait(&lr->notif_ecrivain, &lr->mutex);
    }

    lr->nb_redacteur_actif++;

    pthread_mutex_unlock(&lr->mutex);
}

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
