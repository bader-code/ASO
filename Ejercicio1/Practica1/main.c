#include"timing.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>

int main(){         //Utilizamos el calculo de una funcion exponencial para producir un mayor tiempo en la compilacion del programa y ver como se modifican los tiempos 
	double powxx;
	double pow2x;
	int i;
	double x = 1;
    start();

	for(i = 0; i < INT_MAX; i++){
		x = pow(x,x);
	}
    powxx = pauser();
    printf("Calculo de exponencial pow(x,x): %f microsegundos\n", powxx);
	resume();
	for(i = 0; i < INT_MAX; i++){
		x = pow(2,x);
	}
    pow2x = stop();
    printf("Calculo de exponencial pow(2,x): %f microsegundos\n",pow2x);
    printf("Tiempo total: %f microsegundos\n", powxx + pow2x);
	return 0;
}

