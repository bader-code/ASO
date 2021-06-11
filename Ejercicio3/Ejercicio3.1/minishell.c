#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

char** parse(char *line) {
  static char delim[] = " \t\n"; 
  int count = 0;
  char * p;
  static char **scr ;

  if (*line == '\n')
    return NULL;

  for (p = (char *) strtok(line,delim); p ; p = (char *)strtok(NULL,delim)) {
    scr = (char **) realloc(scr,(count + 2) * sizeof(char *));
    scr[count++] = p;
  }
  scr[count] = NULL;
  return scr;
}

int main() {
  char **argumentos;
  char comando[80];
  pid_t  pid, pid_ret;
  
  setbuf(stdout,NULL);
  printf("\n");
  while (1) {
    do {
      printf("> ");
      fgets(comando,80,stdin);
      argumentos = parse(comando);
    } while(argumentos == NULL);
    
    pid = fork();
  
    switch(pid) {
      case -1: 
        perror("fork");
        exit(1);
        break;
      case 0:
        execvp(argumentos[0], argumentos);        
        perror("execlp"); 
        exit(1);
        break;
      default: 
        break;
    }

    do {
      pid_ret = waitpid(-1,NULL,WNOHANG);
    } while (pid_ret != 0 );  
  
    printf("In parent, my child is %d\n", pid);
  }
} 