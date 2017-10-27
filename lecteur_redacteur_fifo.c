#include "lecteur_redacteur_fifo.h"
#include "linked_list.h"
#include <stdio.h>
// TODO: idée : dès que quelqu'un veut débuter, on le met dans la pile.
// Cela veut dire que tant que ce n'est que des lecteurs, on peut les
// faire tout lire, mais dès qu'on à un rédacteur on bloque,
// faisons sortir tout les lecteurs, et ensuite le rédacteur à
// l'accès solo.

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

    if (! empty(liste_attente)){
        se_mettre_en_attente(1);
    }

    while (nb_redacteur){
        se_mettre_en_attente(1);
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

    nb_lecteur--;

    if (nb_lecteur == 0){
        passer_la_main();
    }

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: debut_redaction
 * Indique le début d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void debut_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    while(nb_redacteur && nb_lecteur > 0){
        //pthread_cond_wait(&lr->notif_ecrivain, &lr->mutex);
        se_mettre_en_attente(0);
    }
    nb_redacteur = 1;

    pthread_mutex_unlock(&lr->mutex);
}

/* fonction: fin_redaction
 * Indique la fin d'une rédaction.
 * lr : le lecteur_redacteur_t à utiliser.
 */
void fin_redaction(lecteur_redacteur_t * lr){
    pthread_mutex_lock(&lr->mutex);

    lr->nb_redacteur = 0;

    passer_la_main();

    pthread_mutex_unlock(&lr->mutex);
}
