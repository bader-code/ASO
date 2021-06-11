#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NONE

int bloquea(int fd, int bloqueo) {
  return 0;
}

#else

int bloquea(int fd, int bloqueo) {
  struct flock c;

  // Si es compartido (F_RDLCK), exclusivo (F_WRLCK) o no tiene bloqueo (F_UNLCK)
  c.l_type = bloqueo;
  c.l_whence = SEEK_SET; // Tipo de offset
  c.l_start = 0; // Offset
  c.l_len = 0; // Longitud de la región bloqueada

  //
  if (fcntl(fd,F_SETLKW,&c) == -1) {
    perror("fcntl");
    exit(-1);
  }
}

#endif

int main() {
  int fd;
  int num,i;

  /* Apertura del fichero */
  fd = open("./temporal", O_CREAT | O_RDWR | O_SYNC, 0666);

  /* Comprobacion de errores */
  for (i=0; i<10 ; i++) {
    lseek(fd,0,SEEK_SET); // Vamos al principio
    bloquea (fd, F_WRLCK); // Bloquea escritura
    if (read(fd,&num,sizeof(int)) == 0 )
      num = 0;
    num++;
    lseek(fd,0,SEEK_SET);
    usleep(500000);
    write(fd,&num,sizeof(int));
    printf("(%d) numero = %i\n",getpid(),num);
    bloquea(fd, F_UNLCK); // Desbloquea
    usleep(500000);
  }

  close(fd);
}