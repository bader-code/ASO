#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

int main() {
  int error;
   struct utsname unameInfo;
  error = uname(&unameInfo)==-1;
    
  if(error == -1){
    perror("Error ");
  }
/* Comprobar si se ha producido un error */
    
/* Completar con los campos adecuados */    
  printf("sistema operativo: %s\n",unameInfo.sysname);
  printf("hostname: %s\n",unameInfo.nodename);
  printf("release: %s\n",unameInfo.release);
  printf("version: %s\n",unameInfo.version);
  printf("maquina: %s\n",unameInfo.machine);        
    
  return 1;
}