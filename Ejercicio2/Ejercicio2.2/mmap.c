#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <ctype.h>



int main(int argc, char* argv[]) {
  int fd;
  struct stat buf;
  size_t mapSize;
  char *texto;
  int i;

  if(argc!=3) {
    printf("Error. Uso: %s nomFich\n", argv[0]);
    exit(-1);
  }

  if((fd = open(argv[1], O_RDWR)) == -1) {
    perror("Fallo en open fd");
    exit(-1);
  }

  //Usar fstat para obtener informacion del fichero.
  if(fstat(fd,&buf) == -1) {
	perror("Fallo en fstat");
	close(fd);
	exit(-1);
   } 

   //2. Comprobar que es un fichero regular
   if(!S_ISREG(buf.st_mode)) {
    fprintf(stderr, "%s no es un directorio.\n", argv[1]);
    exit(1);
  }

  //Obtener el tamaño del fichero
  mapSize = buf.st_size;
  if(mapSize > 200){
    mapSize = 200;
  }

  if(!(texto= mmap(0,mapSize, PROT_READ, MAP_PRIVATE, fd, 0))) { 
     printf ("mmap error for input%s aaa",texto);
     return 0;
  }


  for (i = 0; i < mapSize; i++){
    texto[i] = toupper(texto[i]);
  }
 
 for (i = 0; i < mapSize; i++)
    printf("%c", texto[i]);

 munmap(texto, mapSize);
 close(fd);
 return 1;
}