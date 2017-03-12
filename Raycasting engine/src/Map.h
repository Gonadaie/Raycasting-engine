#ifndef _MAP_
#define _MAP_

#include <SDL.h>
#include "Entity.h"

class Map{

public:
  Map();
  ~Map();
  bool loadMap(char* path);
  void render(SDL_Renderer* renderer, SDL_Rect* miniMap, Entity* player);
  int getCellAt(int x, int y);
  bool isFacingWall(float ox, float oy, bool right, bool up, bool vertical);
  bool collideVertice(unsigned int code, float x, float y);
  float findDistance(float ox, float oy, float angle);

  /*Cast a ray through the map from the coordinate ox;oy and a given angle*/
  float findNearestWall(float ox, float oy, float& ix, float& iy, float angle);

private:
  unsigned int width;
  unsigned int height;
  unsigned int** cells;
  SDL_Rect renderingRect;
};

#endif
