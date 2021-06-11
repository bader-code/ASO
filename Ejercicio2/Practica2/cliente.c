#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>


const char MSG_times[20] = "times";

int main() {
	 fflush(NULL);
	 char pathClient[20], pathServer[20], times[64];
	 srand(time(NULL));
	 pid_t pid = getpid();
	 int fd_FIFO, fd_toClient, fd_toServer, i = 0, iter = rand() % (10 - 1 + 1) + 1;//numero aleatorio entre 1 y 10
	 chdir("/home/");

	 if ((fd_FIFO = open("/tmp/newclient", O_WRONLY)) == -1) {perror("ERROR AL ABRIR newclient"); exit(EXIT_FAILURE);}

	 snprintf(pathClient, sizeof(pathClient), "/tmp/toClient%d", pid);
	 snprintf(pathServer, sizeof(pathServer), "/tmp/toServer%d", pid);
	 if ((mkfifo(pathClient, 0666)) == -1) {perror("ERROR MKFIFO pathclient");exit(EXIT_FAILURE);}
	 if ((mkfifo(pathServer, 0666)) == -1) {perror("ERROR MKFIFO pathServer");exit(EXIT_FAILURE);}

	 if (write(fd_FIFO, &pid, sizeof(pid)) < 0) {perror("ERROR AL ENVIAR EL PID DEL PROCESO");exit(EXIT_FAILURE);}

     if ((fd_toClient = open(pathClient, O_RDONLY)) == -1) {perror("ERROR AL ABRIR toclient");remove(pathClient);remove(pathServer);exit(EXIT_FAILURE);}
	 if ((fd_toServer = open(pathServer, O_WRONLY)) == -1) {perror("ERROR AL ABRIR toServer");remove(pathClient);remove(pathServer);exit(EXIT_FAILURE);}
	 
	 printf("COMIENZO DE LA COMUNICACION\n");
	 while (i < iter) {
		 if (i % 2 == 0) {
			 if(write(fd_toServer, MSG_times, sizeof(MSG_times)) < 0){perror("ERROR AL ESCRIBIR -> fd_toServer");exit(EXIT_FAILURE);}
			 printf("PID : %d | ENVIADO -> %s : ",pid,MSG_times);
			 if(read(fd_toClient, times, sizeof(times)) <  0){perror("ERROR AL LEER -> fd_toClient");remove(pathClient);remove(pathServer);exit(EXIT_FAILURE);}
			 printf("RECIBIDO -> segundos = %s\n", times);
			 }
		 else {
			 printf("PID : %d | NO SE ENVIA NADA : ",pid);
			 if(read(fd_toClient, times, sizeof(times)) < 0){perror("ERROR AL LEER -> fd_toClient");remove(pathClient);remove(pathServer);exit(EXIT_FAILURE);}
             printf("RECIBIDO -> hora = %s\n", times);
			}
			i++;
		}
	 close(fd_toClient);
	 close(fd_toServer);
	 remove(pathClient);
	 remove(pathServer);
	 close(fd_FIFO);
	 return 0;
}
