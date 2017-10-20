#include <semaphore.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex_lecture;
    pthread_mutex_t mutex_ecriture;
} lecteur_redacteur;

void initialiser_lecteur_redacteur(lecteur_redacteur *);
void detruire_lecteur_redacteur(lecteur_redacteur *);
void debut_lecteur(lecteur_redacteur *);
void fin_lecteur(lecteur_redacteur *);
void debut_redaction(lecteur_redacteur *);
void fin_redaction(lecteur_redacteur *);
