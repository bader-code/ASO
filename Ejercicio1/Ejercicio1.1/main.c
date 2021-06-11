#include <stdio.h>

#include "aux.h"
#include "trigo_grados.h"

char* cad[2] = {"No se cumple", "Se cumple"};
extern unsigned char cumple;

int main() {
   double x;
   printf("Introduce un angulo en grados: ");
   scanf("%lf",&x);
   printf("\n");
   checkPita(x);
   printf("Ang: %lf sin()=%lf cos()=%lf. Identidad pitagorica: %s\n",
	x,sinDeg(x),cosDeg(x),cad[cumple]);  	 
   return 0;
}