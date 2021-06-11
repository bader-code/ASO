#include <stdio.h>
#include <sched.h>

// Tipos de planificadores
// SCHED_RR
// SCHED_FIFO
// SCHED_OTHER   

int main() {
  int max, min, act;
  struct sched_param p;
  int sched_policy;

  // Obtencion de la politica de planificacion del proceso actual
  sched_policy = sched_getscheduler(0); 

/*  
Valores máximos y minimos para el planificador 
*/
/*********************************************************************/
  max = sched_get_priority_max(sched_policy);
  min = sched_get_priority_min(sched_policy);
/*********************************************************************/
    
/* 
Obtención de la prioridad del proceso actual 
*/    
/*********************************************************************/
  sched_getparam(0,&p);
  act = p.sched_priority;
/*********************************************************************/

  // Resultado:
  printf("Max:%i \t Min:%i \t Actual:%i \n",max,min,act);
    
  return 0;  
}  