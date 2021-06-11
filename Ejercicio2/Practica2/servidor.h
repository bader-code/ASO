

//-------------MAX TUBERIAS-----------//
#define MAX_TUB 1000


//tipos para de tuberias 
typedef struct {
    int pipe[MAX_TUB];
    int index;
}tPipeLines;

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
void handler_SIGPIPE();




void openlogG(char *text);//Genera los log del programa
void config();//Configuracion de la señal alarm mediante su archivo



