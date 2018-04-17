CC=gcc

CFLAGS=-Wall -Wextra -Werror -O0 -g -std=c11 -pthread
LDFLAGS=-lm

all: grade gradet

aluno: roteadort.c aluno.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o aluno roteadort.c aluno.c

test: roteador.c test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test roteador.c test.c -lm

testt: roteadort.c test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o testt roteadort.c test.c


grade: test
	./test

gradet: testt
	./testt

teste_aluno: aluno
	./aluno

clean:
	rm -rf *.o test testt aluno
