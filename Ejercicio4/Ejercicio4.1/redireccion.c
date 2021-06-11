#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    int pid1, pid2;
    int tuberias[2];
    char buffer[256];
    int fin;
    
    fin = 0;
    
    if(pipe(tuberias) == -1){
        perror("pipe");
        exit(0);
    }
    
    pid1 = fork();
    
    switch(pid1){
        case -1:
            perror("fork");
            exit(0);
            break;
        case 0:
            printf("Lector de la tuberia %i", getpid());
            close(0);
            dup2(tuberias[0],0);
            close(tuberias[0]);
            close(tuberias[1]);
            execlp("wc","wc","-l", NULL);
            exit(0);
            break;
        default:
            break;
    }
    
     pid2 = fork();
    
    switch(pid2){
        case -1:
            perror("fork");
            exit(0);
            break;
        case 0:
            printf("Lector de la tuberia %i", getpid());
            close(0);
            dup2(tuberias[0],0);
            close(tuberias[0]);
            close(tuberias[1]);
            execlp("ls","ls","-l", NULL);
            exit(0);
            break;
        default:
            break;
    }
     close(tuberias[0]);
    close(tuberias[1]);
    wait(NULL);
    printf("fin");
    
}
/**************************************************************************/