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
#include <sys/msg.h>


//--------TAMAÑO MAXIMO DEL MESAJE-----//
#define MAX_MSG 100

//--------MAXIMO DE LCIENTES-----//
#define MAX_CLNT 100

//-----CONSTANTES PARA LOS MENSAJES ftok(...,...);---//
#define QUEUE_CS	'B' //BADR GUAITOUNE AKDI
#define QUEUE_SC	'D'//DANIEL LEDESMA VENTURA
#define KEYFILE "tiempo.lock"//ARCHIVO DEL SISTEMA

//-----ESTRUCTURA DEL MENSAJE QUE SE ENVIA---//
typedef struct{
    long mtype;//TIPO DE MESAJE
    pid_t pid; //PID DEL PROCESO QUE ENVIA EL MENSAJE
    char message[MAX_MSG];//MENSAJE QUE SE ENVIA
}tMsg;

//-----ESTRUCTURA PARA LLEVAR LOS CLIENTES DADOS DE ALTA----//
typedef struct{
    int index;
    pid_t client[MAX_CLNT];
}tClient;

//-----TIPOS DE CONSTANTES PARA LOS MENSAJES----//
#define LONG (sizeof(tMsg) - sizeof (long))


//-----TIPOS DE CONSTANTES PARA LOS MENSAJES----//
const long NEWCLIENT = 1;
const long CLIENT = 2;
const long DELETECLIENT = 3;


//-----MENSAJE QUE SE RECIBE DESDE EL CLIENTE----//
const char MSG_times[20] = "times";


void blockSigns();//Bloqueamos la señales que no vamos a usar
void initSigns();//Iniciamos para cada señal su correscondiente handler
void * iniHandler(int signal, void  *handler);//Enlazamos la señal con su handler



//----HANDLERS PARA CADA SEÑAL----//
void handler_SIGTERM();
void handler_SIGUSR1();
void handler_SIGHUP();
void handler_SIGALARM();




void openlogG(char *text);//Genera los log del programa
void config();//Configuracion de la señal alarm mediante su archivo