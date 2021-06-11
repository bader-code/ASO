#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// funcion que va leyendo 
// de la entrada estandar byte a byte
// y escribiendo lo leido en la salida 
// estandar (hasta que no se detecte nada 
// en la entrada estandar
void copy() {
  char c;
    int error = 0;
    
    do{
       if((read(0, &c, 1) != 1) || (write(1, &c, 1) != 1))     error = 1;
    }  while(c != '\0' && !error);

}


int main( int argc, char **argv)
{
  int  fd;
  char ch;
  
/* Abrir el fichero que se quiere mostrar*/
 fd = open("prueba",O_RDONLY);
/* Hacer lo necesario para que, al llamar 
 a copy, se muestre su contenido por pantalla*/ 
  dup2(fd, 0);
  copy(); 
  return 0;
}