CC=gcc

CFLAGS=-Wall -Wextra -Werror -O0 -g -std=c11 -pthread
LDFLAGS=-lm

all: grade gradet

aluno: roteamentot.c aluno.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o aluno roteamentot.c aluno.c 

test: roteamento.c teste.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test roteamento.c teste.c -lm

testt: roteamentot.c testet.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o testt roteamentot.c testet.c -lm


grade: test
	./test

gradet: testt
	./testt

teste_aluno: aluno
	./aluno

clean:
	rm -rf *.o test testt aluno