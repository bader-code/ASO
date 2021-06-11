#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include  <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

struct tiempo{
	double tu;
	double ts;
	double tt;
};

void mide_tiempo (struct tiempo *t)
{
  int            who;
  struct rusage  uso;
  long           tt1, tt2, tt3, tt4;

  who = RUSAGE_SELF;
  
  getrusage(who, &uso);

  tt1 = uso.ru_utime.tv_usec;
  tt2 = uso.ru_utime.tv_sec;
  tt3 = uso.ru_stime.tv_usec;
  tt4 = uso.ru_stime.tv_sec;

  t->tt = ((double)tt1 * 1.0E-6) 
        +  (double)tt2 
        + ((double)tt3 * 1.0E-6) 
        +  (double)tt4;
  
  t->tu = ((double)tt1 * 1.0E-6) + (double)tt2;

  t->ts = ((double)tt3 * 1.0E-6) + (double)tt4;
}
	
int main() {

  int i,j;
  struct tiempo t1;
  struct tiempo t2;  
  double a = 0.3, b = 0.7;
  unsigned long long int p =0;
  char buffer[16]="123456789012345";

  int fd = open("prueba",O_RDWR | O_CREAT, 0666);
  write(fd,buffer,16);
  mide_tiempo(&t1);
  

  for( i = 0; i < 99999; i++ ) {
    a = sin(a)*cos(b);
    b = a*cos(a);
    for(j = 0; j < 50; j++){
        lseek(fd,0,SEEK_SET);
        read(fd,buffer,16);

    }
    lseek(fd,0,SEEK_SET);
    read(fd,buffer,16);
  }
  close(fd);
  mide_tiempo(&t2);
  
/* Resultados */
  printf("Tiempo de ejecucion: %f sec \n",
          (t2.tt -t1.tt));
  printf("Tiempo de usuario: %f sec \n",
          (t2.tu -t1.tu));
  printf("Tiempo de sistema: %f sec \n",
          (t2.ts -t1.ts) );
}