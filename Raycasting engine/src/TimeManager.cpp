#include <iostream>
#include "TimeManager.h"
#include <SDL.h>

const double SEC = 1000;
double deltaTime = 0;
unsigned int fps = 0;

TimeManager::TimeManager() : before(0), after(0), elapsed(0), ticks(0){};

void TimeManager::update(){
  after = SDL_GetTicks();
  elapsed += deltaTime;
  if(elapsed >= 1){
    elapsed = 0;
    fps = ticks;
    std::cout << fps << std::endl;
    ticks = 0;
  }
  ++ticks;
  deltaTime = (after - before)/SEC;
  before = SDL_GetTicks();
}
