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

}

void fin_lecture(lecteur_redacteur_t * lr){

}

void debut_redaction(lecteur_redacteur_t * lr){

}

void fin_redaction(lecteur_redacteur_t * lr){

}
