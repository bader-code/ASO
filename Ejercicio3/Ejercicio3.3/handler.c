#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int contador_STP=0;
static int contador_INT=0;

void handler(int signo) {
  char m1[80]="Recibida señal SIGTSTP\n";
  char m2[80]="Recibida señal SIGINT\n";   

  if (signo == SIGTSTP) {
    write(1, m1, 80 );
    contador_STP++;        
  }        
        
  if (signo == SIGINT) {
    write(1, m2, 80 );
    contador_INT++;           
  }
}

int main() {

  struct sigaction act;
        
/*   
1. Inicializamos el puntero de la funcion 
*/
/***************************************************************/
     act.sa_handler = handler; 
/***************************************************************/  

/* 
2. Creamos el conjunto de señales en act con SIGINT y SIGSTP 
*/
/***************************************************************/  
     sigemptyset(&act.sa_mask);
     sigaddset(&act.sa_mask, SIGINT); 
     sigaddset(&act.sa_mask, SIGTSTP); 
/***************************************************************/  
  
/* 
3. Opciones del handler a SA_RESTART 
*/
/***************************************************************/  
     act.sa_flags = SA_RESTART; 
/***************************************************************/  
  
/* 
4. Instalamos el controlador para las dos señales 
*/
/***************************************************************/  
     sigaction(SIGINT,  &act, NULL);  
     sigaction(SIGTSTP, &act, NULL);
/***************************************************************/  

  while (contador_STP+contador_INT<10) {};
  printf("Se recibieron %d señales: %d SIGINT y %d SIGTSTP\n", contador_STP+contador_INT, contador_INT,contador_STP);
}