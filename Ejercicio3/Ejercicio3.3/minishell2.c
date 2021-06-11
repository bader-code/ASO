#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

extern int errno;

char ** parse(char *line) {
  static char delim[] = " \t\n";
  int count = 0;
  char * p;
  static char **scr;

  if (*line == '\n')
    return NULL;

  for (p = (char *) strtok(line, delim); p; p = (char *) strtok(NULL, delim)) {
    scr = (char **) realloc(scr, (count + 2) * sizeof(char *));
    scr[count++] = p;
  }
  scr[count] = NULL;

  return scr;
}

void handler(int signo) {
  int errno_bck;
  pid_t pid;
  char m[80]="\nMurió un hijo\n";
  int status;
  int fin=0;

  write(1, m, 80);

  errno_bck = errno;

  while(!fin) {
    pid = waitpid(-1, &status, WNOHANG);
    if (pid == 0)
      fin = 1;
    else if (pid == -1 && errno == ECHILD)
      fin = 1;
    else if (pid == -1) {
      perror("waitpid");
      abort();
    }
  }

  errno = errno_bck;
}

int main() {
  char **argumentos;
  char comando[80];
  pid_t pid, pid_ret;
  struct sigaction act;
/*
Inicializar act convenientemente
*/
/*****************************
 ***********************************/
act.sa_handler = handler;
sigemptyset(&act.sa_mask);
act.sa_flags = SA_RESTART;
sigaction(SIGCHLD,&act,NULL);
/***************************************************************/

  setbuf(stdout, NULL);
  printf("\n");
  while (1) {
    do {
      printf("> ");
      fgets(comando, 80, stdin);
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
  }
}