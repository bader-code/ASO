#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	off_t inicio;
    char linea1[10]="HOLA,";
    char linea2[10]=" mundo";
    int fd;
    
    fd=open("prueba",O_WRONLY|O_CREAT|O_TRUNC,0666);
    
    inicio = lseek(fd,0,SEEK_CUR);
    printf("Principio del archivo %lld\n", inicio);
    
    
    write(fd, linea1, 5);
    
    printf("Posicion despues de escribir %lld\n",lseek(fd,0,SEEK_CUR));
    
    lseek(fd,inicio,SEEK_SET);
    printf("Otra vez al principio %lld\n",lseek(fd,0,SEEK_CUR));

    // saltamos 16KB
    lseek(fd,16384,SEEK_SET);
    
    printf("Escribimos a partir de %lld\n",lseek(fd,0,SEEK_CUR));
    // vuelvo a escribir
    write(fd, linea2, 6);
    close(fd);
    
    return 1;
} 