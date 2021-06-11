#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include"timing.h"


#ifndef TAM_BLOQUE
#define TAM_BLOQUE 1
#endif 

// declarar array para almacenar los bytes leidos
char *buff[TAM_BLOQUE];

int main() {

  int   fdo, fdd,n;
  char  c;

   // mantener este fichero para pruebas iniciales.
  // cambiar por uno mayor para medir tiempos
  fdo = open("/etc/motd", O_RDONLY);

  if( fdo == -1 ) {
    perror("open"); 
    exit(1);
  }

  // Abrir fichero destino para escritura
  fdd = open ("pruba",O_CREAT|O_WRONLY|O_TRUNC, 0660);
  if (fdd == -1) {
  }

  printf("Comienza la copia con TAM_BLOQUE=%d bytes\n", TAM_BLOQUE); 
  // Incluir las llamadas de temporizacion de vuestra libreria (start...)
  // Bucle de copia: leer TAM_BLOQUE btyes por llamada. Escribir lo leido
  

    while((n=read(fdo,buff, TAM_BLOQUE)) > 0) {
         if (write(fdd, buff, n) != n) {
          	perror("Error en write");
	       } 
    }        

  if (n == -1) 
    perror("read");
 
  close(fdo);

}
