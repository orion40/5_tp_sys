CC=gcc
FLAGS=-ggdb -O2
LIBS=-lpthread
IN=test_lecteurs_redacteurs.c lecteur_redacteur.c
OUT=test

all:
	$(CC) $(FLAGS) $(LIBS) $(IN) -o $(OUT)
