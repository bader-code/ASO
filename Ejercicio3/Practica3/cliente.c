#include "servidor.h"

int main() {
	 fflush(NULL);
	 chdir("/home/");/* Por seguridad, cambiamos el directorio de trabajo */
     srand(time(NULL));
	 tMsg msg;
	 int msg_cs, msg_sc , iter = rand() % (10 - 1 + 1) + 1 ,i = 0, solu;
	 key_t key;
     pid_t pid = getpid();

	 key  = ftok(KEYFILE,QUEUE_CS);
     if (key == (key_t)-1){perror("ERROR AL OBTENER CLAVE PARA COLA -> QUEUE_CS ");exit(EXIT_FAILURE);}
	 msg_cs = msgget(key,IPC_CREAT|0600);
     if (msg_cs == -1){perror("ERROR AL OBTENER ID PARA COLA CS");exit (EXIT_FAILURE);}

	 key  = ftok(KEYFILE,QUEUE_SC);
     if (key == (key_t)-1){perror("ERROR AL OBTENER CLAVE PARA COLA -> QUEUE_SC ");exit(EXIT_FAILURE);}
	 msg_sc = msgget(key,IPC_CREAT|0600); 
     if (msg_sc == -1){perror("ERROR AL OBTENER ID PARA COLA SC");exit (EXIT_FAILURE);}


     strcpy (msg.message, "");
     msg.mtype = NEWCLIENT;
     msg.pid = pid;

     if(msgsnd(msg_cs,(struct msgbuf *)&msg,LONG, 0 ) < 0){perror("ERROR CONECTAR CON SERVIDOR");exit (EXIT_FAILURE);}

     printf("COMIENZO DE LA COMUNICACION\n");
	 while (i < iter) {
		 if (i % 2 == 0) {
             strcpy(msg.message,MSG_times); msg.mtype = CLIENT; msg.pid = pid;
             if((solu = msgsnd(msg_cs,(struct msgbuf *)&msg,LONG,0)) < 0){perror("ERROR AL ENVIAR MSG");exit (EXIT_FAILURE);}
	         printf("PID : %d | ENVIADO -> %s : ",pid,MSG_times);
			 if((solu = msgrcv(msg_sc,&msg,LONG,pid,0)) == 0){perror("ERROR AL RECIBIR MSG");exit (EXIT_FAILURE);}
			 printf("RECIBIDO -> segundos = %s\n", msg.message);	
		 }
		else {
             printf("PID : %d | NO SE ENVIA NADA : ",pid);
			 if((solu = msgrcv(msg_sc,(struct msgbuf *)&msg,LONG,pid,0)) < 0){perror("ERROR AL RECIBIR MSG");exit (EXIT_FAILURE);}
			 printf("RECIBIDO -> hora = %s\n", msg.message);
		}
		i++;
	}
    strcpy(msg.message,""); msg.mtype = DELETECLIENT; msg.pid = pid;
	if((solu = msgsnd(msg_cs,(struct msgbuf *)&msg,LONG,0)) < 0){perror("ERROR AL ENVIAR MSG");exit (EXIT_FAILURE);}
	return 0;
}