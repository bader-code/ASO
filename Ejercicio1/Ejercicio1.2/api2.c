#include <errno.h>

extern const char *sys_errlist[];
extern int sys_nerr;
int main() {
  int i;
   for(i = 0; i < sys_nerr; i++){
       printf("%s \n",sys_errlist[i]);
   }                 
  return 1;
}