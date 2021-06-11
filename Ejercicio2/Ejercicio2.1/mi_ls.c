#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>


main(int argc, char *argv[]) {

  struct stat buf;
  DIR   *dirp;
  struct dirent *dent;
  int n;

/* obtencion de la descripcion del directorio */
  if (stat(argv[1], &buf) == -1) {
    perror("stat");
    exit(1);
  }

/* Comprobamos que es un directorio */
  if (!S_ISDIR(buf.st_mode)) {
    fprintf(stderr, "%s no es un directorio.\n", argv[1]);
    exit(1);
  }

/* Apertura del directorio usando operdir*/
  if ((dirp = opendir(argv[1])) == NULL) {
    perror("opendir");
    exit(1);
  }
  printf("<<<< Contenidos de %s>>>>\n",argv[1]);

/* Leemos el directorio */
  while ((dent = readdir(dirp)) != NULL) {
    printf("%d\t%d\t%d\t%s\n", dent->d_ino, dent->d_off, dent->d_reclen, dent->d_name);
  }
  
  // Cerrar directorio
  closedir(dirp);
}