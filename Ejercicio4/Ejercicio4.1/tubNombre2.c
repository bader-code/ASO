
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> 
/**************************************************************************/

// Pasamos la variable de fin a ámbito global
int fin = 0;

/*
Funciones finTub (que pone fin a 1), e ini_manejador
*/
void finTub(int signo) {
/**************************************************************************/
 fin = 1;
/**************************************************************************/
}

void* ini_manejador(int signal, void* manejador) {
/**************************************************************************/
	struct sigaction act;
	struct sigaction old_act;
	act.sa_handler = manejador;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(signal, &act, &old_act);
    return NULL;
/**************************************************************************/
}

int main() {
  int pid;
  int tuberia;
  char buffer[256];

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
        if (buffer[0] == 'q') {
          fin = 1;
          printf("Hijo cierra la tuberia\n");
/*
Se cierra la tubería para generar la señal SIGPIPE al escribir
*/
/**************************************************************************/
          close(tuberia);
/**************************************************************************/
        } else {
          printf("Mensaje recibido(%i): %s\n",getpid(),buffer);
        }
        sleep(5);
      }
      exit(0);
      break;
    default:
      printf("Escritor de la tuberia\n");
/*
Preparamos la señal SIGPIPE
*/
/**************************************************************************/
     ini_manejador(SIGPIPE,finTub);
/**************************************************************************/
      tuberia = open("./tuberia",O_WRONLY);        
      while(!fin) {
        scanf("%s",buffer);
        // Con la tubería cerrada, el write activará la señal SIGPIPE
         write(tuberia,buffer,strlen(buffer)+1);
      }
      printf("Señal recibida 2/2.\n");
      exit(0);
      break;
  } 
  while (wait(NULL)!= -1) {};
  printf("Esto es todo amigos\n");
}