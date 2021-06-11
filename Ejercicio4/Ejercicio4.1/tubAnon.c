#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int pid;
  int tuberias[2];
  char buffer[256];
  int fin;
  fin = 0;
  
  if ( pipe(tuberias) == -1 ) {
    perror("pipe");
    exit(-1);
  }
    
  pid = fork();
  switch (pid) {
    case -1:
      perror("fork");
      exit(-1);
      break;
    case 0:
      printf("Lector de la tuberia\n");
      close(tuberias[1]);
      while (!fin) {
        read(tuberias[0],buffer,256);
        if (buffer[0] == 'q')
          fin = 1;
        else
          printf("Mensaje recibido(%i): %s\n",getpid(),buffer);
      }
      close(tuberias[0]);         
      exit(0);
      break;
    default:
      printf("Escritor de la tuberia\n");
      close(tuberias[0]);
      while(!fin) {
        scanf("%s",buffer);
        write(tuberias[1],buffer,strlen(buffer)+1);
        if (buffer[0] == 'q')
          fin = 1;           
        }
        close(tuberias[1]);
        exit(0);
        break;
  }  
}    