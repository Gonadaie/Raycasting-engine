#include "Game.h"
#include <iostream>
#include <math.h>
#include "constants.h"
#include "trigo_functions.h"
#include <SDL_image.h>
#include <fstream>
#include <cstring> // For strcat()
#include <cstdio> // For sprintf()

using namespace std;

Game::Game(SDL_Renderer* renderer){
  quit = false;

  this->renderer = renderer;
  map = new Map();
  map->loadMap("map.txt");
  miniMap = {(int)(WIDTH-WIDTH/4), 0, (int)(WIDTH/4), (int)(HEIGHT/4)};
  //miniMap = {0, 0, 320, 200};
  inputHandler = new InputHandler();
  timeManager = new TimeManager();
  player = new Player(2, 2);
  projectionPointX = player->getXX();
  projectionPointY = player->getYY();
  textures = new SDL_Texture*[1000];
  for(unsigned int i = 0; i < 1000; ++i)
    textures[i] = NULL;

  loadTextures("./level/textures/");
  SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
  textureRect = {0, 0, 1, 32};
  screenRect = {0, 0, WIDTH, HEIGHT/2};screenRect = {0, 0, WIDTH, HEIGHT/2};
  cout << "Game was created succesfully" << endl;
}

Game::~Game(){
  delete map;
  map = NULL;
  delete inputHandler;
  inputHandler = NULL;
  delete timeManager;
  timeManager = NULL;
  delete player;
  player = NULL;
  for(unsigned int i = 0; i < 1000; ++i){
    if(textures[i] != NULL){
      SDL_DestroyTexture(textures[i]);
      textures[i] = NULL;
    }
  }
  delete[] textures;
  textures = NULL;
  std::cout << "Game terminated succesfully" << std::endl;
}

void Game::run(){
  while(!quit){
    update();
    render();
    //renderMiniMap();
    SDL_RenderPresent(renderer);
  }
}

void Game::update(){
  while(SDL_PollEvent(&e) != 0){

    switch(e.type){
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        inputHandler->setKeyPressed(e.key.keysym.scancode, true);
        break;
      case SDL_KEYUP:
        inputHandler->setKeyPressed(e.key.keysym.scancode, false);
        break;
    }

    if(inputHandler->isKeyPressed(SDL_SCANCODE_ESCAPE))
      quit = true;

  }

  if(inputHandler->isKeyPressed(SDL_SCANCODE_UP))
    player->moveForward();

  if(inputHandler->isKeyPressed(SDL_SCANCODE_DOWN))
    player->moveBackward();

  if(!inputHandler->isKeyPressed(SDL_SCANCODE_LALT)){
    if(inputHandler->isKeyPressed(SDL_SCANCODE_RIGHT))
      player->turnRight();

    if(inputHandler->isKeyPressed(SDL_SCANCODE_LEFT))
      player->turnLeft();
  }

  else{
    if(inputHandler->isKeyPressed(SDL_SCANCODE_RIGHT))
      player->strafeRight();
    if(inputHandler->isKeyPressed(SDL_SCANCODE_LEFT))
      player->strafeLeft();
  }

    timeManager->update();
    player->update();
    SDL_Delay(15);
}

void Game::render(){
  screenRect = {0, 0, WIDTH, HEIGHT/2};
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &screenRect);
  screenRect = {0, 0, WIDTH, HEIGHT/2};
  screenRect.y = HEIGHT/2;
  SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
  SDL_RenderFillRect(renderer, &screenRect);

  projectionPointX = player->getXX()-0.87f; //60/320 <--> FOV/WIDTH
  projectionPointY = player->getYY()-0.87f;

  /*for(int i = -160; i <= 160; ++i){
    float distance = map->findDistance(projectionPoint[0], projectionPoint[1], player->getAngle()+i*0.1875f);
    //cerr << distance << endl;
      if(distance != -1){
        rect = {i + 160, HEIGHT/2-(HEIGHT/distance)/2, 1, HEIGHT/distance};
        SDL_SetRenderDrawColor(renderer, 0xFF/(1+distance/3), 0xFF/(1+distance/3), 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

      }
  }*/

  for(int i = ANGLE_START_VALUE; i <= ANGLE_END_VALUE; ++i){
    float ix;
    float iy;
    float distance = map->findNearestWall(projectionPointX, projectionPointY, ix, iy, player->getAngle()-i*DIFF_BETWEEN_ANGLES);
      if(distance != -1){
        ix -= trunc(ix);
        iy -= trunc(iy);
        distance *= cos(degreesToRadians(i*DIFF_BETWEEN_ANGLES)); //Correct the distance to avoid the "fish eye" effect
        screenRect = {i + ANGLE_END_VALUE, HEIGHT/2-(HEIGHT/distance)/2, 1, HEIGHT/distance};
        textureRect.x = TEXTURE_SIZE * (ix+iy);
        SDL_RenderCopy(renderer, textures[1], &textureRect, &screenRect); //Render walls textures
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF/(1+(10/distance))); //Add shadows
        SDL_RenderFillRect(renderer, &screenRect);
      }
  }
}

void Game::renderMiniMap(){
  map->render(renderer, &miniMap, player);
}

SDL_Texture* Game::loadTexture(SDL_Renderer* renderer, char* path){
  SDL_Surface* img = NULL;
  SDL_Texture* texture = NULL;
  img = IMG_Load(path);
  if(img != NULL){
    texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);
    std::cout << path << " loaded succesfully" << std::endl;
    return texture;
  }
  else{
    std::cerr << "Unable to load " << path << std::endl;
    return NULL;
  }
}

void Game::loadTextures(char* path){
  /*This function has to deal with C function because mingw doesn't know how to find std::to_string() which is quite annoying.
  And because I'm an annoying man, I thought that C code was a proper solution.*/

  char* filePath = new char[strlen(path) + 8]; //Max textures number = 999, 3 digit + ".png" + '\0'

  char* textureNumber = new char[4]; // 3 digits + '\0'
  for(unsigned int i = 0; i < 1000; ++i){
    sprintf(filePath, ""); //Empty the string
    strcat(filePath, path);
    sprintf(textureNumber, "%u", i);
    strcat(filePath, textureNumber);
    strcat(filePath, ".png");
    ifstream f(filePath);
    if(f.good()){
      textures[i] = loadTexture(renderer, filePath);
      f.close();
    }
  }
  delete[] filePath;
  filePath = NULL;
}
