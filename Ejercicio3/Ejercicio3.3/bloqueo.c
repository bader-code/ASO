#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  sigset_t grupo;
  sigset_t pendientes;
  int tiempo = 5; // por defecto 5s
       
/* 
Inicializar el conjunto de señales 'grupo' con las señales de interrupcion SIGINT, y parada SIGTSTP
*/
/***************************************************************/
     sigemptyset(&grupo);
     sigaddset(&grupo,SIGINT);
     sigaddset(&grupo,SIGTSTP);   
/***************************************************************/
    
/* 
Bloquear el grupo de señales creado 
*/
/***************************************************************/
     sigprocmask(SIG_BLOCK, &grupo, NULL);
/***************************************************************/
   
  if (argv[1]) 
    tiempo = atoi(argv[1]); 
    
  printf("Durmiendo %d segundos con (sleep)\n", tiempo);
  sleep(tiempo);
/* 
Comprobar qué señales (grupo pendientes) se enviaron mientras el proceso estaba dormido 
*/
/***************************************************************/
     sigpending(&pendientes);
/***************************************************************/
   
  if (sigismember(&pendientes, SIGINT)) {
    printf("Presionaste ctrl+c, no la trato\n");
  }        
    
  if (sigismember(&pendientes, SIGTSTP)) {
    printf("Presionaste ctrl+z, la desbloqueo (a dormir)\n");
/* 
Desbloquear la señal SIGTSTP 
*/
/***************************************************************/
     sigdelset(&grupo,SIGINT);
     //sigdelset(&grupo,SIGTSTP);
     sigprocmask(SIG_UNBLOCK, &grupo, NULL);
/***************************************************************/
    printf("Desperté otra vez \n");
  }            
  return 0;
}    