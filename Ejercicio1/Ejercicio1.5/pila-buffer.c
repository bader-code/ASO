#include <stdio.h>

/* Código para comprobar robustez frente a intentos de desbordar la pila */
/* 1. ¿Cambiará el valor de alguna variable durante/tras la llamada a foo()? */

/* 2. Trata de forzar una Violación de Segmento. ¿Por que se produce? */

/* 3 Trata de conseguir que cambie el valor de las variables 'despues' y/o 'antes'  sin que se produzca la Violación de Segmento */

/* 4. Soluciona el problema! */

void foo() {
  unsigned char antes[2] = {9,9};
  char nombre[16];
  unsigned char despues[2] = {10,10};

  printf("antes %d (%p) despues %d (%p) nombre %p\n",antes[0],&antes,despues[0],&despues,nombre);
  printf("Introduce una cadena: ");
  gets(nombre);
  printf("cadena: %s antes %d despues %d\n",nombre,antes[0],despues[0]);
  return;
}

int main() {
  int local = 8;
  
  printf("local antes de la llamada: %d\n",local);
  foo();
  printf("local tras la llamada: %d\n",local);

  return 1;
}
