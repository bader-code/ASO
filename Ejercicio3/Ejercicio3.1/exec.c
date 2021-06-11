#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
int main() {
  int rv;
    
  execlp("ps", "ps", "-le", NULL);

  perror("execlp");
  printf("\n\n El Comando terminó correctamente\n\n");
}