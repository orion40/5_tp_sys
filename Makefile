CC=gcc
CFLAGS=-ggdb -O2
LIBS=-lpthread
MAIN=test_lecteurs_redacteurs
LECTEUR=lecteur_redacteur
REDACTEUR=redacteur_lecteur
FIFO=lecteur_redacteur_fifo
OUT_LECTEUR=lecteurs_first
OUT_REDACTEUR=redacteurs_first
OUT_FIFO=fifo

all: $(OUT_LECTEUR) $(OUT_REDACTEUR) $(OUT_FIFO)

$(OUT_LECTEUR): $(OUT_LECTEUR).o
	$(CC) $(FLAGS) $(LIBS) $(MAIN).o $(LECTEUR).o -o $(OUT_LECTEUR) -DLECTEUR

$(OUT_REDACTEUR): $(OUT_REDACTEUR).o
	$(CC) $(FLAGS) $(LIBS) $(MAIN).o $(REDACTEUR).o -o $(OUT_REDACTEUR) -DREDACTEUR

$(OUT_FIFO): $(OUT_FIFO).o
	$(CC) $(FLAGS) $(LIBS) $(MAIN).o $(FIFO).o -o $(OUT_FIFO) -DFIFO

$(OUT_LECTEUR).o:
	$(CC) $(FLAGS) $(MAIN).c $(LECTEUR).c -c -DLECTEUR

$(OUT_REDACTEUR).o:
	$(CC) $(FLAGS) $(MAIN).c $(REDACTEUR).c -c -DREDACTEUR

$(OUT_FIFO).o:
	$(CC) $(FLAGS) $(MAIN).c $(FIFO).c -c -DFIFO

clean:
	rm $(OUT_LECTEUR) $(OUT_REDACTEUR) $(OUT_FIFO) *.o
