/*
Includes:
*/
/***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <unistd.h>

/***************************************************************/

volatile int contador=0;

void alarma (int signo) {
  char m[80]="Se acabo la cuenta\n";
  write(1,m,80);
  contador ++;
}

void* ini_manejador(int signal, void *manejador) {
  struct sigaction act;
  struct sigaction old_act;

  int i;

  act.sa_handler = manejador;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(signal, &act, &old_act);
}

int main(int argc, char **argv) {

  struct itimerval it;
  int segundos;
  
/* 
Inicializar el manejador con la funcion ini_manejador 
*/
/***************************************************************/
    ini_manejador(SIGALRM, alarma);
/***************************************************************/
    
  segundos = atoi(argv[1]);
  it.it_value.tv_sec = segundos;
  it.it_value.tv_usec = 0;
  it.it_interval.tv_sec = segundos;
  it.it_interval.tv_usec = 0;

/* 
Inicializar el reloj de pared (wall-clock) mediante setitimer 
*/
/***************************************************************/
   if(setitimer(ITIMER_REAL,&it,NULL) == -1){
    perror("setitimer");
    exit(1);
   }
/***************************************************************/

  while(contador<5){};
  printf("Recibidas %d veces la señal de alarma\n",contador);
  return 0;
}