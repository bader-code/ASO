/*
Includes:
*/
/***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
 #include <unistd.h>
/***************************************************************/

#define PIDSIZE  6

extern int errno;

int main() {
  int pid;
  char c_pid[7];
  c_pid[6]='\0';    
    
  // Leer el pid de la entrada estandar
  fgets(c_pid, PIDSIZE, stdin);

  while (strcmp(c_pid,"quit\n")!=0) {
    if (strcmp(c_pid,"ps\n")==0) {
/*
Ejecutar la orden ps
*/
/***************************************************************/
     system("ps");
/***************************************************************/
    } else {
      pid=atoi(c_pid);
/* 
Evitamos que se envie una señal a nuestro proceso 
*/
/***************************************************************/
      if (pid == getpid())
/***************************************************************/
        printf("A mi no \n");
      else
/* 
Envio efectivo de la señal, al proceso mensaje selectivo de error 
*/
/***************************************************************/
        if (kill(pid,SIGKILL) == -1) {
/***************************************************************/
          printf("\t no puede matarlo!!! ");
          if (errno == ESRCH)
            printf("(no existe)\n");
          if (errno == EPERM)
            printf("(no se deja)\n");
        }
        else
          printf("\t muerto!!! \n");
    }
    // Nuevo pid
    fgets(c_pid, PIDSIZE, stdin);
  }
  return 0;
}