#include <pthread.h>

typedef struct {
    int nb_redacteur_actif;
    int nb_lecteur_actif;
    int nb_lecteur_attente;
    pthread_mutex_t mutex;
    pthread_cond_t notif_ecrivain;
    pthread_cond_t notif_lecteur;
} lecteur_redacteur_t;

void initialiser_lecteur_redacteur(lecteur_redacteur_t *);
void detruire_lecteur_redacteur(lecteur_redacteur_t *);
void debut_lecture(lecteur_redacteur_t *);
void fin_lecture(lecteur_redacteur_t *);
void debut_redaction(lecteur_redacteur_t *);
void fin_redaction(lecteur_redacteur_t *);
