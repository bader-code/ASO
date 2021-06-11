#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

int main() {
  int  fd1;

  char *buf;
  struct stat statbuf;
  int n;
  //Crea un fichero (open)
  fd1 = open("prueba", O_WRONLY|O_CREAT|O_TRUNC);

  /* Creacion de un enlace hard */
  link("prueba", "pruebaLinkH");

  /* Enlace simbolico */
  symlink("prueba", "pruebaLinkS");
 
  // Usar lstat para ver el tamaño de ambos 
   
   lstat("pruebaLinkH",&statbuf);
   printf("Tamaño total en bytes pruebaLinkH:%ld \n",statbuf.st_size);
   printf("Tamaño total en bloques pruebaLinkH:%ld \n",statbuf.st_blocks);


   lstat("pruebaLinkS",&statbuf);
   printf("Tamaño total en bytes pruebaLinkS:%ld \n",statbuf.st_size);
   printf("Tamaño total en bloques pruebaLinkS:%ld \n",statbuf.st_blocks);
  return 0;
}