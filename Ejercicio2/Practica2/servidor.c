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
#include <stdlib.h>

#include "servidor.h"

extern int errno;

//-----------TUBERIAS----------------//
tPipeLines readers;
tPipeLines writers;


//----------DESCRIPTOR DEL FICHERO---------------------// 
int fdLock;

//-----ESTRUCTURAS NECESARIAS PARA LA SEÑAL SIGALARM---//
struct itimerval it;

//-----CONJUNTO DE DESCRIPTORES PARA SELECT()------//
fd_set setReadFiles;

//------CONJUNTO DE SEÑALES QUE BLOQUEAREMOS-------//
sigset_t signs;


//-----VARIABLES QUE INDICA QUE UN DESCRIPTOR SE HA CERRADO Y CUAL-----//
int SIG_EPIPE = 0;
int indexPP;


void openlogG(char *text){
	 setlogmask (LOG_UPTO (LOG_NOTICE));
	 openlog("DEMONIO", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);
	 syslog(LOG_NOTICE, "%s",text);
	 closelog();

}

void config(){
     int fd;
     char buffer[20];
     if((fd = open("/home/tiempo.conf", O_RDWR)) == -1){
		 openlogG("NO EXISTE -> tiempo.conf  -> /home/\n");
		 for (int i = 0; i < readers.index; i++)  {if (readers.pipe[i] != -1) close(readers.pipe[i]);}
		 for (int i = 0; i < writers.index; i++)  {if (writers.pipe[i] != -1) close(writers.pipe[i]);}
		 remove("/tmp/newclient");
		 remove("tiempo.lock");
		 exit(EXIT_FAILURE);
     }
	 printf("config()\n");
	 read(fd, buffer, sizeof(int));
	 close(fd);
     it.it_value.tv_sec = atoi(buffer);
     it.it_value.tv_usec = 0;
     it.it_interval.tv_sec = atoi(buffer);
	 it.it_interval.tv_usec = 0;
     setitimer(ITIMER_REAL, &it, NULL);
}


void handler_SIGALARM() {
	 char hour[30];
     time_t t = time(NULL);
	 struct tm *tm = localtime(&t);
	 strftime(hour, 100, "%H : %M : %S", tm);
	 for (int i = 1; i < writers.index; i++) {
		 if (writers.pipe[i] != -1) {
			 if (((write(writers.pipe[i],hour, sizeof(hour))) == -1) && (errno == EPIPE)) {
				 SIG_EPIPE = 1;
				 indexPP = i;
			 }
		 }
	 }
}
void handler_SIGHUP() {
	 openlogG("LEYENDO -> tiempo.conf -> handler_SIGHUP()\n");
	 config();
}
void handler_SIGUSR1() {
	 char hour[30], cadena[1024];
	 time_t t = time(NULL);
	 struct tm *tm = localtime(&t);
	 strftime(hour, 100, "%H : %M : %S", tm);
	 snprintf(cadena, sizeof(cadena), "SEÑAL handler_SIGUSR1(), HORA ACTUAL = %s\n", hour);
	 openlogG(cadena);
}
void handler_SIGTERM() {
	 close(fdLock);
	 if (remove("tiempo.lock") == -1) {openlogG("NO SE PUEDE ELIMINAR -> tiempo.lock\n");}
	 if (remove("/tmp/newclient") == -1) {openlogG("NO SE PUEDE ELIMINAR -> newclient\n"); }
	 for (int i = 0; i < readers.index; i++) {if (readers.pipe[i] != -1) close(readers.pipe[i]);}
	 for (int i = 0; i < writers.index; i++) {if (writers.pipe[i] != -1) close(writers.pipe[i]);}
	 openlogG("EJECUACION FINALIZADA CORRECTAMENTE\n"); 
	 exit(EXIT_SUCCESS);
}
void handler_SIGPIPE() {
	if(SIG_EPIPE == 1){
		 FD_CLR((int)readers.pipe[indexPP], &setReadFiles);								
	     close(writers.pipe[indexPP]); close(readers.pipe[indexPP]);
	     writers.pipe[indexPP] = -1; readers.pipe[indexPP] = -1;
		 SIG_EPIPE = 0;
	     openlogG("TUBERIA CERRADA -> handler_SIGPIPE()\n");
	}
}

void * iniHandler(int signal, void  *handler){
	struct sigaction act , old_act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(signal, &act, &old_act);
}

void initSigns() {
	 iniHandler(SIGALRM, handler_SIGALARM);
	 iniHandler(SIGHUP,  handler_SIGHUP);
	 iniHandler(SIGUSR1, handler_SIGUSR1);
	 iniHandler(SIGTERM, handler_SIGTERM);
	 iniHandler(SIGPIPE, handler_SIGPIPE);
}
void blockSigns() {
	 sigfillset(&signs);
	 sigdelset(&signs, SIGALRM);sigdelset(&signs, SIGHUP);sigdelset(&signs, SIGUSR1);
	 sigdelset(&signs, SIGTERM);sigdelset(&signs, SIGPIPE);
	 sigprocmask(SIG_BLOCK, &signs, NULL);
}




void demonio(){
	 int pid , cambios, max, fd_toClient, fd_toServer, cmp;
	 struct timeval timeout;
	 char pathClient[20],pathServer[20],cadena[20];
	 FD_ZERO(&setReadFiles);
	 readers.pipe[0] = open("/tmp/newclient", O_RDONLY);
	 FD_SET(readers.pipe[0], &setReadFiles);
	 max = readers.pipe[0];
	 writers.pipe[0] = -1;
	 readers.index = 1;
	 writers.index = 1;
	 while (1) {
		 FD_ZERO(&setReadFiles);
		 for (int i = 0; i <= readers.index ; i++) {
			if (readers.pipe[i] > -1) {
				 FD_SET(readers.pipe[i], &setReadFiles);
				 max = max < readers.pipe[i]? readers.pipe[i] : max;
			}
		 }
		 cambios = select(max + 1, &setReadFiles, NULL, NULL, &timeout);
		 if (cambios == 0) {
			 openlogG("SELECT -> timeout\n"); 
		 }
		 else{
			 if (FD_ISSET(readers.pipe[0], &setReadFiles)) {
				 if(read(readers.pipe[0], &pid, 20) > 0){
				     snprintf(pathServer, sizeof(pathServer), "/tmp/toServer%d", pid);
				     snprintf(pathClient, sizeof(pathClient), "/tmp/toClient%d", pid);
				     fd_toClient= open(pathClient, O_WRONLY);
					 fd_toServer = open(pathServer, O_RDONLY);
					 if (fd_toServer != -1 && fd_toClient != -1) {
						writers.pipe[writers.index] = fd_toClient;
						writers.index++;
						readers.pipe[readers.index] = fd_toServer;
						readers.index++;
					 }
			    }
			 }
			 else{
				 for (int i = 1; i < readers.index ; i++) {
					 if (FD_ISSET(readers.pipe[i], &setReadFiles)) {
						 if(read(readers.pipe[i], cadena, sizeof(cadena)) == -1){perror("ERROR LECTURA");exit(EXIT_FAILURE);}
						 cmp = strcmp(cadena, MSG_times);
						 if(cmp == 0){
							 time_t tim = time(NULL);
						     sprintf(cadena, "%d", (int)tim);
						     write(writers.pipe[i], cadena, sizeof(cadena));
						 }
					 }
				 }
			 }
		 }
	 }
}

int main() {
	 pid_t pid;
	 char pid_char[20];
	 mkfifo("/tmp/newclient", 0666);
     
	 pid = fork();/* Forkeamos el proceso padre */
	 if (pid < 0) {perror("FALLO EN FORK");exit(EXIT_FAILURE);}
	 if (pid > 0) {exit(EXIT_SUCCESS);}/* Cuando tenemos un PID correcto podemos cerrar el proceso padre.*/
	 
	 umask(0);/* Cambiamos el modo de la mascara de ficheros para que los fichero generados por el  demonio sean accesibles por todo el mundo */
	 chdir("/home/");/* Por seguridad, cambiamos el directorio de trabajo */
	 if (setsid() < 0) {perror("ERROR en NEWSID"); exit(EXIT_FAILURE);}/* Creamos un nuevo SID para que el sistema se haga cargo del proceso huérfano*/
	 close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);/* Cerramos los descriptores standard, son posible riesgo de seguridad.*/
	 
	 if ((fdLock = open("tiempo.lock", O_RDWR | O_CREAT, 0640)) < 0) {perror("ERROR AL ABRIR -> tiempo.lock");exit(EXIT_FAILURE);}/**/
	 if (lockf(fdLock, F_TLOCK, 0) < 0) {perror("ERROR AL BLOQUEAR -> tiempo.lock");exit(EXIT_FAILURE);}/*Bloqueando el fichero garantiza unica instancia*/
	 sprintf(pid_char, "%d\n", getpid());
	 write(fdLock, pid_char, sizeof(pid_char));/*Escribiendo el PID en archivo*/
	 

	 config();/*Leemos el archivo de configuracion para ver el periodo*/
	 blockSigns();/*Bloquemanos las señales que no vamos a usar*/
	 initSigns();/*Inicializamos las señales en sus respectivos handlers o manejadores*/
	 
	 demonio();
}


