CC=gcc
CFLAGS=-ggdb -O2
LIBS=-lpthread
IN_LECTEUR=test_lecteurs_redacteurs.c lecteur_redacteur.c
IN_REDACTEUR=test_lecteurs_redacteurs.c redacteur_lecteur.c
IN_FIFO=test_lecteurs_redacteurs.c lecteur_redacteur_fifo.c
OUT_LECTEUR=lecteurs_first
OUT_REDACTEUR=redacteurs_first
OUT_FIFO=fifo

all:
	$(CC) $(FLAGS) $(LIBS) $(IN_LECTEUR) -o $(OUT_LECTEUR) -DLECTEUR
	$(CC) $(FLAGS) $(LIBS) $(IN_REDACTEUR) -o $(OUT_REDACTEUR) -DREDACTEUR
	$(CC) $(FLAGS) $(LIBS) $(IN_FIFO) -o $(OUT_FIFO) -DFIFO

clean:
	rm $(OUT_LECTEUR) $(OUT_REDACTEUR) $(OUT_FIFO)
