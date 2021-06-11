#SRC=$(wildcard *.c)
#OBJ=$(SRC:.c=.o)
#CFLAGS= -g -Wall -fPIC -ggdb

#all:dinamic 

#dinamic:$(OBJ)
#	gcc -shared -fPIC -o ejecutable lib/libtrigo.so  $^ -ldl

#static:$(OBJ)
#	gcc -o ejecutable1 $^ -Llib/ -ltrigo -lm

#%.o:%.c 
#	gcc  $(CFLAGS) -c  $< -o $@
#clean:
#	rm -f  ejecutable *.o


#SRC=$(wildcard *.c)
#OBJ=$(SRC:.c=.o)
#CFLAGS= -g -Wall

#all:static

#static:libA
#	sh script.sh lib
#	mv *.a lib

#dinamic:libSO
#	sh script.sh lib
#	mv *.so lib

#libA:sincos.o asinacos.o
#	ar cr libtrigo.a $<
#libSO:sincos.o asinacos.o 
#	ar cr libtrigo.so $<
#%.o:%.c 
#	gcc $(CFLAGS) -c $< -o $@
#clean:
#	rm -f ejemplo1 *.o *.a *.so

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
CFLAGS= -g -Wall 


all:$(OBJ)
	gcc $^ -o ejecutable -lm

%.o:%.c 
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f ejemplo1 ejecutable *.o
