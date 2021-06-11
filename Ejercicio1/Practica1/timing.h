#ifndef _TIEMPO_H_
#define _TIEMPO_H_

/**************OPCIONES DE CLKID EN EL ARCHIVO DE CONFIGURACION*************/
/*
       CLOCK_REALTIME
       CLOCK_REALTIME_COARSE 
       CLOCK_MONOTONIC
       CLOCK_MONOTONIC_COARSE
       CLOCK_PROCESS_CPUTIME_ID
       CLOCK_THREAD_CPUTIME_ID 
*/


/********************FUNCIONES******************************/

/*• void start() tomará el instante actual como referencia para el contador.*/
void start();

/*• int pause() parará temporalmente la cuenta asociada al contador.
Devuelve el tiempo transcurrido desde el último resume().
Si el contador ya estaba en pausa, esta llamada se ignora.*/
double pauser();

/*• void resume() continúa la cuenta tras una pause().
Si el contador no estaba en pausa, esta llamada se ignora.*/
void resume();

/*• int stop() para definitivamente el contador Devuelve el tiempo transcurrido desde la última llamada a resume() ( o start() si nunca se llamó a pause() ).*/
double stop();/*para el timer definitivamente y devuelve el tiempo en microsegundos*/

#endif
