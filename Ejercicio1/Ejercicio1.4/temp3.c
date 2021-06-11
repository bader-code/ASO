#include <sys/types.h>
#include <time.h>
#include <stdio.h>

int main() {

 time_t ahora = time(NULL);
  struct tm* ahoralocal = localtime(&ahora);

  printf ("Tiempo UNIX: %ld\n", ahora);
  printf ("Tiempo humano: %02d/%02d/%d %02d:%02d:%02d\n", ahoralocal->tm_mday,
      ahoralocal->tm_mon +1,    /* Sumamos 1 al mes porque va desde 0 a 11 */
      ahoralocal->tm_year+1900,
      ahoralocal->tm_hour,
      ahoralocal->tm_min,
      ahoralocal->tm_sec);
/* Declarar t_hoy, t_ayer */    
    
/* Tiempo actual (hoy)*/

/* Imprimir la fecha de hoy */
    
  //printf("Hoy es:%s",);

/* Calcular el tiempo ayer */
    
  //t_ayer = ;

/* Imprimir el tiempo ayer */

  printf("Ayer fue:%s",);    
  return 1;
}