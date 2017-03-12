#include "Entity.h"
#include <math.h>
#include "TimeManager.h"
#include <iostream>
#include "trigo_functions.h"

using namespace std;

Entity::Entity(float x, float y){
  xx = x;
  yy = y;
  vx = 0;
  vy = 0;
  speed = 5;
  angle = 90;
  cx = trunc(xx);
  cy = trunc(yy);
  rect = {cx, cy, 4, 4};
}

void Entity::update(){

  xr += vx*deltaTime;
  yr += vy*deltaTime;

  if(xr >= 1){
    ++cx;
    --xr;
  }

  if(xr <= 0){
    --cx;
    ++xr;
  }

  if(yr >= 1){
    ++cy;
    --yr;
  }

  if(yr <= 0){
    --cy;
    ++yr;
  }

  xx = cx+xr;
  yy = cy+yr;

  rect.x = (int)(xx*4) - 2;
  rect.y = (int)(yy*4) - 2;

  vx*=friction;
  vy*=friction;

  //cerr << "P-angle : "<< angle << "-----------------------------" << endl;

}

void Entity::moveForward(){
  vx = speed*cos(angle*3.14f/180);
  vy = -speed*sin(angle*3.14f/180);
}

void Entity::moveBackward(){
  vx = -speed*cos(angle*3.14f/180);
  vy = speed*sin(angle*3.14f/180);
}

void Entity::turnRight(){
  angle -= 135*deltaTime;
  updateAngle(angle);
}

void Entity::turnLeft(){
  angle += 135*deltaTime;
  updateAngle(angle);
}

void Entity::strafeRight(){
  vx = speed*cos((angle-90)*3.14f/180);
  vy = -speed*sin((angle-90)*3.14f/180);
}

void Entity::strafeLeft(){
  vx = speed*cos((angle+90)*3.14f/180);
  vy = -speed*sin((angle+90)*3.14f/180);
}

short Entity::getAngle(){
  return (short)angle;
}

SDL_Rect* Entity::getRect(){
  return &rect;
}

float Entity::getXX(){
  return xx;
}

float Entity::getYY(){
  return yy;
}
