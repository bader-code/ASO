#include <stdio.h>
#include <unistd.h>

#ifndef BUF_MODE
#define BUF_MODE 0
#endif

int main() {
  int i = 0;
  // setvbuf(stdout,(char*)NULL,_IONBF,BUFSIZ);
  switch(BUF_MODE) {
    case 1:
/*******************************************************************************/
        setvbuf(stdout,(char*)NULL,_IONBF,BUFSIZ);
/*******************************************************************************/
        break;
    case 2:
/*******************************************************************************/
         setvbuf(stdout,(char*)NULL,_IOLBF,BUFSIZ);
/*******************************************************************************/
        break;
    case 3:
/*******************************************************************************/
         setvbuf(stdout,(char*)NULL,_IOFBF,BUFSIZ);
/*******************************************************************************/
        break;
    default:
        break;
  } 
  for (i = 0; i< 5; i++) {
    printf("Esta es la ");
    sleep(1);
    printf("Linea %d\n", i);
    getc(stdin);
  }
  printf("Final\n");
  return 0;
}