#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {

  char *buf;
  struct stat statbuf;
  int n;

/* leemos las propiedades del link mediante lstat */
  if (lstat(argv[1], &statbuf) == -1) { 
    perror("lstat"); 
    exit(1);
  }
/* Comprobamos si es un link o no */
  if (!S_ISLNK(statbuf.st_mode))  {
    fprintf(stderr, "%s is not a symbolic link.\n",
              argv[1]);
		exit(1);
  }

/* Reservamos espacio para el link (+1 final de cadena */
  buf = (char*)malloc(statbuf.st_size + 1);

  if (buf == NULL) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }

/* Leemos el link */
  n = readlink(argv[1], buf, statbuf.st_size + 1);

  if(n == -1){
    perror("readlink"); 
    exit(1);
  }

/* Imprimimos el link buffer */  
  buf[n] ='\0'; //Caracter de fin de cadena 
  printf("%s\n", buf);
  exit(0);
  
}