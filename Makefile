CC=gcc
CFLAGS=-ggdb -O2
LIBS=-lpthread
IN_LECTEUR=test_lecteurs_redacteurs.c lecteur_redacteur.c
IN_REDACTEUR=test_lecteurs_redacteurs.c redacteur_lecteur.c
IN_FIFO=test_lecteurs_redacteurs.c lecteur_redacteur_fifo.c
OUT_LECTEUR=lecteurs_first
OUT_REDACTEUR=redacteurs_first
OUT_FIFO=fifo

all: $(OUT_LECTEUR).o $(OUT_REDACTEUR).o $(OUT_FIFO).o
	$(CC) $(FLAGS) $(LIBS) $(OUT_LECTEUR).o -o $(OUT_LECTEUR) -DLECTEUR
	$(CC) $(FLAGS) $(LIBS) $(OUT_REDACTEUR).o -o $(OUT_REDACTEUR) -DREDACTEUR
	$(CC) $(FLAGS) $(LIBS) $(OUT_FIFO).o -o $(OUT_FIFO) -DFIFO

$(OUT_LECTEUR).o:
	$(CC) $(FLAGS) $(IN_LECTEUR) -c -DLECTEUR

$(OUT_REDACTEUR).o:
	$(CC) $(FLAGS) $(IN_REDACTEUR) -c -DREDACTEUR

$(OUT_FIFO).o:
	$(CC) $(FLAGS) $(IN_FIFO) -c -DFIFO

clean:
	rm $(OUT_LECTEUR) $(OUT_REDACTEUR) $(OUT_FIFO) *.o
