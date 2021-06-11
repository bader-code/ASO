#include "servidor.h"

extern int errno;

//-----------COLA DE MENSAJES------------//
int msg_cs, msg_sc;
key_t key;

//-------ESTRUCTURA PARA MANDAR ALARMA A LOS CLIENTES---//
tClient all_client;

//----------DESCRIPTOR DEL FICHERO---------------------// 
int fdLock;

//-----ESTRUCTURAS NECESARIAS PARA LA SEÑAL SIGALARM---//
struct itimerval it;

//------------CLAVE PARA LA COLA DE MENSJAES-------------//
key_t key;

//------------VARIABLE PARA LAS SEÑALES-------------//
sigset_t signs;


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
		 remove("tiempo.lock");
		 exit(EXIT_FAILURE);
     }
	 read(fd, buffer, sizeof(int));
	 close(fd);
     it.it_value.tv_sec = atoi(buffer);
     it.it_value.tv_usec = 0;
     it.it_interval.tv_sec = atoi(buffer);
	 it.it_interval.tv_usec = 0;
     setitimer(ITIMER_REAL, &it, NULL);
}


void handler_SIGALARM() {
	 char hour[30], cadena[1024];
     tMsg msg;
     time_t t = time(NULL);
	 struct tm *tm = localtime(&t);
	 strftime(hour, 100, "%H : %M : %S", tm);
	 for (int i = 0; i < all_client.index; i++) {
		 if (all_client.client[i] != -1) {
             msg.mtype = all_client.client[i];
             msg.pid = getpid();
			 strcpy(msg.message,hour);
			 if(msgsnd(msg_sc,(struct msgbuf *)&msg,LONG,0) == -1){
                 snprintf(cadena, sizeof(cadena), "SEÑAL handler_SIGALARM(), ERROR AL ENVIAR HORA ACTUAL = %s AL CLIENTE : %d\n", hour,all_client.client[i]);
	             openlogG(cadena);
		     }
	     }
     }
}
void handler_SIGHUP() {
	 printf("handler_SIGHUP()\n");
	 openlogG("LEYENDO -> tiempo.conf -> handler_SIGHUP()\n");
	 config();
}
void handler_SIGUSR1() {
	 char hour[30], cadena[1024];
	 time_t t = time(NULL);;
	 struct tm *tm = localtime(&t);;
	 strftime(hour, 100, "%H : %M : %S", tm);
	 snprintf(cadena, sizeof(cadena), "SEÑAL handler_SIGUSR1(), HORA ACTUAL = %s\n", hour);
	 openlogG(cadena);
}
void handler_SIGTERM() {
	 close(fdLock);
	 if (remove("/home/tiempo.lock") == -1) {openlogG("NO SE PUEDE ELIMINAR -> tiempo.lock\n");}
     msgctl(msg_cs,IPC_RMID,NULL);
	 msgctl(msg_sc,IPC_RMID,NULL);
	 openlogG("EJECUACION FINALIZADA CORRECTAMENTE\n"); 
	 exit(EXIT_SUCCESS);
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
}

void blockSigns() {
	 sigfillset(&signs);
	 sigdelset(&signs, SIGALRM);sigdelset(&signs, SIGHUP);sigdelset(&signs, SIGUSR1);
	 sigdelset(&signs, SIGTERM);
	 sigprocmask(SIG_BLOCK, &signs, NULL);
}




void demonio(){
     pid_t pid;
	 tMsg msg;
     char cadena[100];	
     int cmp, solu;
     all_client.index = 0;

	 key  = ftok(KEYFILE,QUEUE_CS);
     if (key == (key_t)-1){perror("ERROR AL OBTENER CLAVE PARA COLA -> QUEUE_CS");exit(EXIT_FAILURE);}
	 msg_cs = msgget(key,IPC_CREAT|0600);
     if (msg_cs == -1){perror("ERROR AL OBTENER ID PARA COLA CS");exit (EXIT_FAILURE);}

	 key  = ftok(KEYFILE,QUEUE_SC);
     if (key == (key_t)-1){perror("ERROR AL OBTENER CLAVE PARA COLA -> QUEUE_SC");exit(EXIT_FAILURE);}
	 msg_sc = msgget(key,IPC_CREAT|0600); 
     if (msg_sc == -1){perror("ERROR AL OBTENER ID PARA COLA SC");exit (EXIT_FAILURE);}

     while(1){
         if((solu = msgrcv(msg_cs,(struct msgbuf *)&msg,LONG,NEWCLIENT,IPC_NOWAIT)) > 0){
             all_client.client[all_client.index++] = msg.pid;
         }
         if((solu = msgrcv(msg_cs,(struct msgbuf *)&msg,LONG,CLIENT,IPC_NOWAIT)) > 0){
             cmp = strcmp(msg.message,MSG_times); 
			 if(cmp == 0){
                 time_t tim = time(NULL);
				 sprintf(cadena, "%d", (int)tim);
		         strcpy(msg.message,cadena);
                 msg.mtype = msg.pid;
                 msgsnd(msg_sc,(struct msgbuf *)&msg,LONG,0);
			 }
		 }
         if((solu = msgrcv(msg_cs,(struct msgbuf *)&msg,LONG,DELETECLIENT,IPC_NOWAIT)) > 0){
             int i = 0;
             while(i <= all_client.index){
				 if(all_client.client[i] == msg.pid){
					 all_client.client[i] = -1;
                     i = all_client.index + 1;
				 }
                 i++;
			 }	
         }
         solu = 0;
     }
}

int main() {
	 pid_t pid;
	 char pid_char[20];
     
	 pid = fork();/* Forkeamos el proceso padre */
	 if (pid < 0) {perror("FALLO EN FORK");exit(EXIT_FAILURE);}
	 if (pid > 0) {exit(EXIT_SUCCESS);}/* Cuando tenemos un PID correcto podemos cerrar el proceso padre.*/
	 
	 umask(0);/* Cambiamos el modo de la mascara de ficheros para que los fichero generados por el  demonio sean accesibles por todo el mundo */
	 chdir("/home/");/* Por seguridad, cambiamos el directorio de trabajo */
	 if (setsid() < 0) {perror("ERROR en NEWSID"); exit(EXIT_FAILURE);}/* Creamos un nuevo SID para que el sistema se haga cargo del proceso huérfano*/
	 close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);/* Cerramos los descriptores standard, son posible riesgo de seguridad.*/
	 
	 if ((fdLock = open("/home/tiempo.lock", O_RDWR | O_CREAT, 0640)) < 0) {perror("ERROR AL ABRIR -> tiempo.lock");exit(EXIT_FAILURE);}/**/
	 if (lockf(fdLock, F_TLOCK, 0) < 0) {perror("ERROR AL BLOQUEAR -> tiempo.lock");exit(EXIT_FAILURE);}/*Bloqueando el fichero garantiza unica instancia*/
	 sprintf(pid_char, "%d\n", getpid());
	 write(fdLock, pid_char, sizeof(pid_char));/*Escribiendo el PID en archivo*/
	 

	 config();/*Leemos el archivo de configuracion para ver el periodo*/
	 blockSigns();/*Bloquemanos las señales que no vamos a usar*/
	 initSigns();/*Inicializamos las señales en sus respectivos handlers o manejadores*/
	 
	 demonio();//
}
