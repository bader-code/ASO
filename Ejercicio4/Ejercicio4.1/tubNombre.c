#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int pid;
  int tuberia;
  char buffer[256];
  int fin;
    
  fin = 0;
  mkfifo("./tuberia",0666);
  pid = fork();
    
  switch (pid) {
    case -1:
      perror("fork");
      exit(-1);
      break;
    case 0:
      printf("Lector de la tuberia\n");
      tuberia = open("./tuberia",O_RDONLY);
      while (!fin) {
        read(tuberia,buffer,256);
        if (buffer[0] == 'q')
          fin = 1;
        else
          printf("Mensaje recibido(%i): %s\n",getpid(),buffer);
        sleep(5);
      }
      close(tuberia);         
      exit(0);
      break;
    default:
      printf("Escritor de la tuberia\n");
      tuberia = open("./tuberia",O_WRONLY);        
      while(!fin) {
        scanf("%s",buffer);
        write(tuberia,buffer,strlen(buffer)+1);
        if (buffer[0] == 'q')
          fin = 1;           
      }
      close(tuberia);
      exit(0);
      break;
  }    
}
