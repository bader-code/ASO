#!/bin/bash
#SRC=$(wildcard *.c)
#OBJ=$(SRC:.c=.o)
CFLAGS= -g -Wall -Werror -fPIC -ggdb
#lib/ -lmitiempo
all: app
	gcc -o app main.o -L lib/ -lmitiempo -lm -O2

app: static
	gcc -c main.c


dinamic: libreria.o 
	ar cr libmitiempo.so $<
	sh script.sh lib
	mv libmitiempo.so lib

static: libreria.o 
	ar cr libmitiempo.a $<
	sh script.sh lib
	mv libmitiempo.a lib

%.o:%.c 
	gcc $(CFLAGS) -c $< -o $@

clean:
	-rm app
	-rm *.o
	-rm -r lib