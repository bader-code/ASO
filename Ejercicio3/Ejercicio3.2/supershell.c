#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  int max;
  struct sched_param p;
  int sched_policy;

  sched_policy = SCHED_RR;
/* 
Obtencion del valor máximo de prioridad de 'tiempo real'
*/
/*********************************************************************/
  max = sched_get_priority_max(sched_policy);
/*********************************************************************/

/* 
Fijamos la prioridad del proceso a la máxima 
*/
  p.sched_priority = max;
/*********************************************************************/
  if (sched_setscheduler(getpid(),sched_policy,&p) == -1) {
/*********************************************************************/
    perror("sched_setscheduler");
    exit(-1);
  }

  // Ejecutamos una shell que heredará las propiedades del padre
  execl("/bin/bash","/bin/bash",(char *) 0 );

  // Comprobar que se heredan las prioridades con el programa prio
  return 0;
}