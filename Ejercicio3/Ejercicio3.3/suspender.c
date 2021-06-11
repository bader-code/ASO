#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo) {
  char m[80]="Recibida señal SIGINT\n";   
  write(1, m, 80 );
}

int main() {

  struct sigaction act;
  sigset_t seniales;

/*   
1. Inicializamos el puntero de la funcion 
*/
/***************************************************************/
   act.sa_handler = handler; 
/***************************************************************/
  
/* 
2. Creamos el conjunto de seniales en act a vacio
*/
/***************************************************************/
   sigemptyset(&act.sa_mask);
/***************************************************************/
  
/* 
3. Opciones del handler a SA_RESTART
*/
/***************************************************************/
    act.sa_flags = SA_RESTART; 
/***************************************************************/
  
/*
4. Instalamos el controlador para la señal SIGINT 
*/
/***************************************************************/
    sigaction(SIGINT,  &act, NULL); 
/***************************************************************/
    
/*
5. Crear el conjunto de señales por las que esperaremos
*/
/***************************************************************/
   sigfillset(&seniales);
   sigdelset(&seniales,SIGINT);
/***************************************************************/

/*
6. Suspender el proceso.
*/
/***************************************************************/
   sigsuspend(&seniales);
/***************************************************************/
  
  printf("Continuo la ejecucion\n");  
  return 1;
}  