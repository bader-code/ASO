
/**************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
/**************************************************************************/

#ifndef NHIJOS 
#define NHIJOS 2
#endif

// TIpo de datos para las variables que enviamos/leemos por el pipe
typedef struct _dato_t {
  int index;
  int tiempo;
} _t_dato_; 

int terminaHijo = 0;

void finTub(int signo) {
  terminaHijo = 1;
}

void* ini_manejador(int signal, void* manejador) {
  struct sigaction act;
  struct sigaction old_act;

  act.sa_handler = manejador;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(signal, &act, &old_act);
  return NULL;
}
 
/* 
Función que ejecutará cada hijo. 
- index es el índice el bucle for del padre cuando se creó el hijo
- fd es el descriptor de fichero de extremo de escritura de una tubería
*/
void fhijo(int index,int fd) {
  int r;
/* 
Preparar el código para capturar la señal SIGPIPE usando ini_manejador.
La función que trate dicha señal, deberá poner terminaHijo a 1
*/
/**************************************************************************/
 ini_manejador(SIGPIPE,finTub);
/**************************************************************************/
  srand(time(NULL));
  while (!terminaHijo) {
    _t_dato_ dato;
    r  = rand() % 15 + 4;
    sleep(r);
    printf("Hijo %d escribe en pipe el tras dormir %ds\n",index,r);
/* 
Escribimos en la tubería el índice y el tiempo dormido.
Creamos una estructura de tipo _t_dato para incluir ambos enteros.
*/
    dato.index = index;
    dato.tiempo = r;
/**************************************************************************/
   if(write(fd,&dato,sizeof(dato))== -1){
       printf("Write en el hijo %d falla.\n");
   }
/**************************************************************************/
  }
  printf("Hijo %d: el padre dice que a terminar!!\n", index);
}

int main() {
  int pid;
  int tuberias[2];
  int tpadre[NHIJOS];
  fd_set conjunto;
  int i=0;    
  struct timeval timeout;

  for (i=0; i<NHIJOS; i++) {
/* 
Crear NHIJOS tuberías e hijos. Cada tubería permitirá comunicación unidireccional 
entre el padre y un hijo (el hijo escribirá y el padre leerá).
*/
/**************************************************************************/
   if(pipe(tuberias)==-1){
       perror("pipe");
       exit(-1);
   }
   pid = fork();
/**************************************************************************/
    switch (pid) {
      case -1:
        perror("fork");
        exit(-1);
        break;
      case 0:
/* 
Cada hijo hará una llamada a fhijo. El primer argumento será  i. 
El segundo, el descriptor del extremo de escritura de su tubería.
*/ 
/**************************************************************************/
     close(tuberias[0]);
     fhijo(i,tuberias[1]);
/**************************************************************************/
        exit(0);
        break;
      default:
/**************************************************************************/
        close(tuberias[1]);
        tpadre[i] = tuberias[0];
/**************************************************************************/
        sleep(1); // Esperar a que el hijo empiece ...
        break;
    }    
  }
    
  int cambios;
  while(1) {
    printf("Padre hace select.\n");
    // El proceso padre se queda en un bucle haciendo select para saber cuándo 
    // debe leer de alguna tubería/entrada estándar.
    FD_ZERO(&conjunto);
    FD_SET(0, &conjunto); // incluye stdin en el conjunto
/* 
Incluir resto de descriptores en el conjunto.
*/
    for (i=0;i<NHIJOS;i++) {
/**************************************************************************/
    FD_SET(tpadre[i], &conjunto);
/**************************************************************************/
    }
/*
Establecer el timeout y llamada a select
*/
/**************************************************************************/
   timeout.tv_sec = 15;
   timeout.tv_usec = 0;
   cambios = select(NHIJOS + 1,&conjunto,NULL,NULL,&timeout);
/**************************************************************************/
    if (cambios == 0) {
      printf("timeout de select\n");
    }
    else {
      // Comprobar si hay algo en la entrada estándar
      if (FD_ISSET (0, &conjunto)) {
        char* line = NULL;
        size_t size = 0;
        printf("Algo hay en la entrada estándar ... ");
        getline(&line, &size, stdin);
        line[strlen(line)-1] = '\0';
        printf("Leído: %s\n",line);
/*
Comprobar si hay que terminar.
  Si es así (porque se recibe exit), cerrar todos los descriptores de lectura para
  que se genere la señal SIGPIPE para cada hijo.
  Luego, hacer un bucle invocando "wait()" para esperar a que mueran todos los hijos.
*/
/**************************************************************************/
   if(strcmp(line,"exit") == 0){
     for(i = 0; i < NHIJOS; i++){
       close(tpadre[i]);
     }
     while(wait(NULL) == -1);
     exit(0);
   }
/**************************************************************************/
      } 
/*
Comprobar si hay algo en alguna tubería. Si es así, leer e imprimir por pantalla
*/
      for (i = 0; i < NHIJOS;  ++i) {
        if (FD_ISSET (tpadre[i], &conjunto)) {
          _t_dato_ dato;
          read(tpadre[i],&dato,sizeof(dato));
          printf("Padre recibe por hijo %d con tiempo  %d\n",dato.index,dato.tiempo);
        }
      }
    }
  }
} 