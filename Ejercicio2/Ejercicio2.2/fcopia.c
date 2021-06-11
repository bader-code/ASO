#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#ifndef TAM_BLOQUE
#define TAM_BLOQUE 1
#endif
#ifndef FFLUSH
#define FFLUSH 1
#endif 

// declarar array para almacenar los bytes leidos
char *buff[TAM_BLOQUE];

int main(int argc, char *argv[]) {

  FILE  *fdo, *fdd;
  int n;
  char  c;

   // mantener este fichero para pruebas iniciales.
  // cambiar por uno mayor para medir tiempos
  fdo = fopen(argv[1], "r");

  if(fdo == NULL) {
    perror("open"); 
    exit(1);
  }

  // Abrir fichero destino para escritura
  fdd = fopen (argv[2],"w");
  if (fdd == NULL) {
       perror("open"); 
       exit(1);
  }

  printf("Comienza la copia con TAM_BLOQUE=%d bytes\n", TAM_BLOQUE); 
  // Incluir las llamadas de temporizacion de vuestra libreria (start...)
  // Bucle de copia: leer TAM_BLOQUE btyes por llamada. Escribir lo leido
  int i = 0;
    while((n=fread(buff,1,TAM_BLOQUE,fdo)) > 0) {
         if (fwrite(buff, 1,n, fdd) != n) {
          	perror("Error en write");
	       } 
         // if(FFLUSH==1 && flush(NULL)!=0){
            // perror("Error en flush");
          //}
    }        
  if (n == -1) 
    perror("read");

  fclose(fdo);

  return 1;
}
 