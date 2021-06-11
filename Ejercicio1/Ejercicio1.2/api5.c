#include <stdio.h>
#include <unistd.h>

int main() {
    /* Obtener la información indicada con la función pathconf*/
    printf("Max. enlaces: %d\n", pathconf("/",_PC_LINK_MAX));
    printf("Max. longitud del path: %d\n",pathconf("/",_PC_PATH_MAX));
    printf("Max. longitud de nombre: %d\n",pathconf("/",_PC_NAME_MAX));
    
    /* Obtener los mismos datos para otro sistema de ficheros */

    return 1;
}