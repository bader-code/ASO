#include <math.h>

#include "trigo_grados.h"

// recibe el angulo en grados
double sinDeg(double x) {
 return sin( (x*M_PI)/180.0 );
}


double cosDeg(double x) {
 return cos( (x*M_PI)/180.0 );
}