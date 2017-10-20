CC=gcc
FLAGS=-O2 -ggdb -std=c99
IN=test_lecteurs_redacteurs.c
OUT=test

all:
	$(CC) $(FLAGS) $(IN) -o $(OUT)
