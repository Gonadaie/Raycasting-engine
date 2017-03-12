#ifndef _ENTITY_
#define _ENTITY_

#include <SDL.h>

static const float friction = 0.9f;

class Entity{

public:
  Entity(float x, float y);
  void update();
  SDL_Rect* getRect();
  void moveForward();
  void moveBackward();
  void turnRight();
  void turnLeft();
  void strafeRight();
  void strafeLeft();
  short getAngle();
  float getXX();
  float getYY();

protected:
  int cx;
  int cy;
  float xr;
  float yr;
  float xx;
  float yy;
  float vx;
  float vy;
  float speed;
  float angle;
  SDL_Rect rect;
};

#endif
