#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Uso: %s fichero-a-copiar fichero-destino\n", argv[0]);
    exit(1);
  }    
  FILE* fp = fopen(argv[1], "r");
  FILE* fpo = fopen(argv[2], "w");
  int ch;
  struct stat stats;

  if (fp == NULL) {
    perror("fopen"); return 1;
  }

  if (fstat(fileno(fp), &stats) == -1) { // POSIX only
    perror("fstat"); return 1;
  }

  printf("BUFSIZ is %d, but optimal block size is %ld\n", BUFSIZ, stats.st_blksize);
  if (setvbuf(fp, NULL, _IOFBF, stats.st_blksize) != 0) {
    perror("setvbuf failed"); // POSIX version sets errno
    return 1;
  }

  while ((ch=fgetc(fp)) != EOF) fwrite(&ch,1,1,fpo);

  fclose(fp);
  fclose(fpo);
}