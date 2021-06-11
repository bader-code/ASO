#include <sys/param.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  char  *dir;
  long  pathmaxlen;
  
/* Obtencion de la longitud máxima del path */  
  pathmaxlen = pathconf(".", _PC_PATH_MAX);  

/* Obtencion del directorio actual */
  dir = getcwd((char *)NULL, 0);

  if(dir == NULL) { 
    perror("getcwd"); 
    exit(1); 
  }
/* Imprimir resultados + eliminacion de memoria */
  printf("CWD: %s\n", dir);
  free(dir);

/* Cambio al directorio tmp */
  if(chdir("/tmp") == -1) {
    perror("chdir");
  }

/* Mostramos el nuevo directorio, la longitud de la cadena
   la pasamos como la máxima más el final de cadena */
  dir = getcwd((char *)NULL, pathmaxlen + 1);

  if (dir == NULL) {
    perror("getcwd");
  }

  printf("CWD: %s (%lu)\n", dir,sizeof(dir));

  free(dir);
}