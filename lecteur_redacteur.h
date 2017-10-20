#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex_lecture;
    pthread_mutex_t mutex_ecriture;
} lecteur_redacteur_t;

void initialiser_lecteur_redacteur(lecteur_redacteur_t *);
void detruire_lecteur_redacteur(lecteur_redacteur_t *);
void debut_lecture(lecteur_redacteur_t *);
void fin_lecture(lecteur_redacteur_t *);
void debut_redaction(lecteur_redacteur_t *);
void fin_redaction(lecteur_redacteur_t *);
