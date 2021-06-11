#include <sys/time.h>
#include <time.h>
#include <stdio.h>

/* Tras completar el código, prueba a compilarlo con diferentes niveles
de optimización y comprueba las diferencias de tiempo.
Trata de encontrar un codigo que requiera mas tiempo de CPU en el bucle
*/

int main() {
  int i;
  struct timespec start, end;
  double t_ini,t_fin,a=0.0, time_spent;
/* Declarar tv_ini, tv_fin, t_ini y t_fin */
   clock_gettime(CLOCK_REALTIME, &start);     
/* Obtener el tiempo actual */
  for (i=0;i<10000;i++)
    a++;
    
/* Obtener el tiempo actual */
    for(i = 0; i <10000; i++){
      a = a*a*a / (i*i);
      a = a*a/a*a/a*a/a*a/a*a/a*a;
    }

  clock_gettime(CLOCK_REALTIME, &end);  

  time_spent = (end.tv_sec - start.tv_sec)*1000.0 + (end.tv_nsec - start.tv_nsec)/1.0e6;
/* Calcular el número de segundos total */
    
  t_ini =(double) ( t_ini + (1 * 1E-6) );
  t_fin =(double) ( t_fin + (1 * 1E-6) );    
    
/* Imprimir resultados */    
  //printf("tini=%f, tfin=%f dif=%f\n",t_ini,t_fin);
  printf("time_spent=%f\n",time_spent);
  return 1;
}