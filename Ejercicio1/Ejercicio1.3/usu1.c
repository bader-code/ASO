#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
/* Declarar apropiadamente las 
   variables usuario y efectivo */

/* Obtener uid del proceso */       
   int usuario = getuid();
/* Obtener uid efectivo del proceso */    
   int efectivo = getuid();
    
  printf("UID = %d EUID = %d\n",usuario,efectivo);
    
  if (usuario == efectivo)
    printf("Son iguales\n");
  else
    printf("Interesante. UID = (%d) EUID = %d\n",usuario);
    
  return 1;                
}
