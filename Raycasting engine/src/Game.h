#ifndef _GAME_
#define _GAME_

#include <SDL.h>
#include "Map.h"
#include "InputHandler.h"
#include "TimeManager.h"
#include "Player.h"

class Game {

public:
  Game(SDL_Renderer* renderer);
  ~Game();
  void run();
  void update();
  void render();
  void renderMiniMap();
  SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
  void loadTextures(char* path);

private:
  bool quit;
  SDL_Renderer* renderer;
  SDL_Event e;
  Map* map;
  InputHandler* inputHandler;
  Player* player;
  TimeManager* timeManager;
  SDL_Rect miniMap;
  SDL_Rect textureRect;
  SDL_Rect screenRect;
  float projectionPointX;
  float projectionPointY;
  unsigned int* renderedWall;
  SDL_Texture** textures;
};

#endif
