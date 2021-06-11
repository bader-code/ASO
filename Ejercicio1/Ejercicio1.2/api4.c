	
#include <unistd.h>
#include <stdio.h>

int main() {
  /* Obtener la información indicada con la función sysconf */
  printf("ticks/seg: %d\n",sysconf(_SC_CLK_TCK));
  printf("Max. files: %d\n",sysconf(_SC_OPEN_MAX));
  printf("Tamaño de pagina: %d\n",sysconf(_SC_PAGESIZE));
  printf("Max. Hijos: %d\n",sysconf(_SC_CHILD_MAX));
    
  return 1;
}