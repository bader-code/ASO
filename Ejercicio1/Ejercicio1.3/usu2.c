#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <shadow.h>

int main() {
/* Definir apropiadamente usuario y su estructura pw */
struct spwd *info;
    
/* Obtener el uid del proceso    */
uid_t usuario = getuid();
    
/* Obtener la informacion de usuario con el identificador */
  printf("Entro al sistema como %s(uid:%d)\n",usuario);

/* Imprimir el pasword del usuario */
info = getspnam("badr");
printf("passwd %s\n",info->sp_pwdp);

/* Tratar de obtener la informacion de usuarioso con getspnam() 
e imprimir el passwd*/

/* Si no es posible usar getspnam(), explica por que y busca una solucion */
  return 1;
}
