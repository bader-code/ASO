#include <unistd.h>
#include <errno.h>
#include <stdio.h>


int main() {
  char a[13]="noexiste.dat";
  int error;
  error = setuid(0);
  open(a, 0);
  perror("Error ");
/* Comprobar la ocurrencia de error
   y usar perror para especificarlo */
           
  return 1;
}