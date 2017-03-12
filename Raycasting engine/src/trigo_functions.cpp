#include "trigo_functions.h"
#include <math.h>
#include "constants.h"
#include <stdlib.h>

float distanceBetween(float x1, float y1, float x2, float y2){
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void updateAngle(float& angle){
  if(angle > 360)
    angle -= 360;
  if(angle < 0)
    angle += 360;
}

float degreesToRadians(float angle){
  angle = angle*PI/180;
  return angle;
}
