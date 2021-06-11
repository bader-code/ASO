#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
/***************************************************************************/
// includes:

/***************************************************************************/

int main() {
/* 
Definicion de los descriptores. Utiliza tantos descriptores y archivos como
necesites para responder a las preguntas. Se pueden reutilizar descriptores.
*/
  int  fd1, fd2;

/***************************************************************************/
//1. ¿Qué combinación de flags para la función `open` serían equivalentes a la invocación de la función `creat`?
// Código para responder a la pregunta 1:
fd1 = open("prueba", O_WRONLY|O_CREAT|O_TRUNC);
/***************************************************************************/
/***************************************************************************/


//2. ¿Qué flag o combinación de flags serían necesarios para que la función `open` devolviese un error si se intenta crear un fichero que ya existe?
// Código para responder a la pregunta 2:
fd1 = open("prueba", O_WRONLY|O_CREAT|O_EXCL);
if (fd1<0){
    if(errno==EEXIST){
         perror( "open EEXIST" );
    }
}
/***************************************************************************/
/***************************************************************************/

//¿Bajo qué circunstancia la función `open` devolverá un error de tipo `ENOENT`? En esa circunstancia, ¿qué flag evitaría dicho error?
// Código para responder a la pregunta 3:
fd1 = open("prueba", O_WRONLY);
if (fd1<0) {        /* error */ //-1 si errno==ENOENT fichero no existe;
    if(errno==ENOENT){
        perror( "open ENOENT" );
    }
}
//Flag O_CREAT 	0100 	El fichero deberá ser creado si no existía previamente.
/***************************************************************************/
/***************************************************************************/

//¿Bajo qué circunstancia o circunstancias (combinación de `flags` y tipo de fichero), la función `open` devolverá un error de tipo `EISDIR`?
// Código para responder a la pregunta 4:

fd1 = open("/home", __O_DIRECTORY | O_RDWR);
if (fd1<0){      /* error */ //-1 si errno==ENOENT fichero no existe;
    if(errno==EISDIR){
        perror( "open EISDIR" );
    }
}


/***************************************************************************/
/***************************************************************************/
//5. ¿Bajo qué circunstancia la función `open` devolverá un error de tipo `ENAMETOOLONG`? 
// Código para responder a la pregunta 5:
char d_name[255 + 5];
fd1 = open(d_name,O_WRONLY);
if (fd1<0){   
    if(errno==ENAMETOOLONG){
        perror( "open ENAMETOOLONG" );
    }
}
/***************************************************************************/
/***************************************************************************/
// Cierre de los ficheros:
close(fd1);
/***************************************************************************/

  return 1;
}