#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t  pid;
  int    status;

  switch(pid = fork()) {   

  case -1:
    perror("fork");
    exit(1);

  case 0:
    printf("Soy el hijo\n");
    exit(0);
    
  default:
    break;
  }

  if (waitpid(pid, &status, 0) == -1) {
    perror("waitpid");
    exit(1);
  }

  if (WIFEXITED(status))
  	printf("El hijo terminó con codigo de salida %d.\n", WEXITSTATUS(status));
  if (WIFSTOPPED(status))
    printf("El hijo fue detenido por la señal %d.\n", WSTOPSIG(status));    
  if (WIFSIGNALED(status)) 
    printf("El hijo fue terminado por la señal %d.\n", WTERMSIG(status));
    
  return 0;
}