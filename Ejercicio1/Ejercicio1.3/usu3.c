#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
    uid_t usuario;
    gid_t gid_usuario;
    struct passwd *info = getpwnam("badr");
    usuario = info->pw_uid;
    gid_usuario = info->pw_gid;
   /* Código destinado a ejecutarse con privilegios elevados */
    printf("My UID is: %d. My GID is: %d \n", geteuid(), getegid());
    system("/usr/bin/id");
   /* Eliminar temporalmente los privilegios */
    if (setuid(usuario)!= 0 && setgid(gid_usuario) != 0) {
     /*Error de manejo */
     printf("Error");
     perror("seteuid");
     return -1;
    }
    /* Código destinado a ejecutarse SIN privilegios*/
    printf("My UID is: %d. My GID is: %d \n", geteuid(), getgid());
    system("/usr/bin/id");
    if (seteuid (0)!= 0 && setegid(0) != 0) {
     /* Error de manejo*/ 
     printf("Error");
     perror("seteuid");
     return -1;
    }
    /* Código destinado a ejecutarse con privilegios elevados */
    printf("My UID is: %d. My GID is: %d \n", getuid(), getgid());
    system("/usr/bin/id");
    return 1;
}