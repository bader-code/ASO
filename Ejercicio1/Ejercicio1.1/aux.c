#include <math.h>

#include "aux.h"
#include "trigo_grados.h"
 
unsigned char cumple = 0;
static double eps = 0.001;

// sen2+ cos2 = 1
void checkPita(double ang) {
  double sin2 = sinDeg(ang)*sinDeg(ang);
  double cos2 = cosDeg(ang)*cosDeg(ang);
  cumple = fabs((sin2+cos2)-1)< eps ? 1: 0;
}