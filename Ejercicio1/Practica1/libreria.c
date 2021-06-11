#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "timing.h"
#include <time.h>



typedef enum {start_e,resume_e,pause_e,stop_e}tEstado; //Enumerado para mantener el estado de la ejecucion del programa, start(corriendo), pause(parado), stop(fin), resume(corriendo)

struct timespec contador;              //struct timespec {
											 //time_t tv_sec;   segundos 
											 //largo tv_nsec;   nanosegundos 
									   //}; 

clockid_t precision;  //clock_id

tEstado estado;        

const clockid_t clocks[] = {
    CLOCK_REALTIME,
	CLOCK_REALTIME_COARSE,
    CLOCK_MONOTONIC,
	CLOCK_MONOTONIC_COARSE,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID,
    
  };



const char* parseClockid_t[] = {
    "CLOCK_REALTIME",
	"CLOCK_REALTIME_COARSE",
    "CLOCK_MONOTONIC",
	"CLOCK_MONOTONIC_COARSE",
    "CLOCK_PROCESS_CPUTIME_ID",
    "CLOCK_THREAD_CPUTIME_ID",
    
};

//Parsea la opcion introducida en el archivo de configuracion
clockid_t parser(char *buffer){
	int i = 0;
	while(i < sizeof(parseClockid_t)){
		if(strcmp(buffer,parseClockid_t[i]) == 0){
			return clocks[i];
		}
		i++;
	}
	exit(1);
}


//Inicio del programa
void start(){
	FILE *fp;
	char *buffer = malloc(PATH_MAX);
	int nBytes;
	if((fp = fopen("conf.txt", "r")) == NULL){
		perror("Fallo al intentar abrir el fichero conf.txt");
		exit(1);
	}
	else{
		if((nBytes = fread(buffer,PATH_MAX,1,fp)) == -1){
			perror("Fallo de lectura");
			exit(1);
		}
		buffer[nBytes - 1] = '\0';
		precision = parser(buffer);
		clock_gettime(precision,&contador);
		estado = start_e; 
	}
}


//Calcula el tiempo en microsegundos y lo devuelve
double tiempo(struct timespec start, struct timespec end){
	return(end.tv_sec - start.tv_sec)*1000.0 + (end.tv_nsec - start.tv_nsec)/1.0e6;
}


//Para el programa y devuelve el tiempo transcurrido desde el start o el ultimo resume
double pauser(){
	if(estado == start_e){
		struct timespec pause_t;
		clock_gettime(precision,&pause_t);
		estado = pause_e;  //Paramos el estado
		return tiempo(contador, pause_t);
	}
	return 0.0;
}



//Continua la cuenta tras un pause
void resume(){
	if(estado == pause_e){
		clock_gettime(precision,&contador);
		estado = start_e;
	} 
}


//Para definitivamente el contador, devuelve el tiempo transcurrido desde es start o desde el ultimo resume
double stop(){
	if(estado == start_e){
		struct timespec stop;
		clock_gettime(precision,&stop);
		estado = stop_e;
		return tiempo(contador, stop);
	}
	return 0.0;
}