#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* VARIABLES DE ENTORNO */
/* Codifica un programa con 2 posibles argumentos 
*  -l  (por defecto) lista el valor de todas las variabls de entorno
* -e <nombre> establece el valor de la variable EDITOR al especificado. 
*             Si la variable EDITOR ya existia previamente, 
*	      escribira por pantalla su valor anterior antes de modificarla
*
* 1. Ejecuta el codigo en un terminal y comprueba (tras la finalizacion) 
* si la variable EDITOR se ve realmente modificada Â¿por que?. 
* 2. Ejecuta el codigo declarando antes (en el shell) la variable EDITOR 
* a cualquier valor. 
*/

extern char** environ;
 extern char* optarg;
int main(int argc, char* argv[]) {	
     char** variable;
     char* edit;
     int option;
     while((option = getopt(argc,argv,"le"))){
         switch(option){
             case 'e':
            if(edit = getenv("EDITOR") != NULL){
		        printf("%s", "El valor de EDITOR es: ", edit);
		        setenv("EDITOR", optarg, 1);
	         }
          break;
             default : for(variable = environ; *variable = NULL; ++variable){
                        printf("%s\n", *variable);
                       } 
                       break;
         }
     }

  return 1;
  
}

/*extern char** environ;
extern char* optarg;

int main(int argc, char* argv[]) {
	
  char** variable;
  char* edit;
  int opt;
  while(opt = getopt(argc, argv, "le:") != -1){
      switch(opt){
          case 'e':
            if(edit = getenv("EDITOR") != NULL){
		        printf("%s", "El valor de EDITOR es: ", edit);
		        setenv("EDITOR", optarg, 1);
	        }
            break;
          case 'l':
            for(variable = environ; *variable = NULL; ++variable){
	     	     printf("%s", *variable);
	  	    }
            break;
          default: for(variable = environ; *variable = NULL; ++variable){
	     	     printf("%s", *variable);
	  	    }
            break;
        
        }
      }
  return 1;
}*/
