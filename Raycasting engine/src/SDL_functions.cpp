#include <iostream>
#include <SDL.h>
#include "SDL_functions.h"
#include "constants.h"
#include <SDL_image.h>

using namespace std;

bool initSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0 && !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		cerr << "SDL could not initialize : " << SDL_GetError() << endl;
		return false;
	}
	else
		return true;
}

bool createWindow(SDL_Window** window, const unsigned int width, const unsigned int height){
	*window = SDL_CreateWindow("Raycasting Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_SHOWN);
	if(*window != NULL)
		return true;
	else{
		cerr << "Could not create the window : " << SDL_GetError() << endl;
		return false;
	}
}

void setFullScreen(SDL_Window* window, SDL_Renderer* renderer, bool b){
	if(b){
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetScale(renderer, RWIDTH/WIDTH, RHEIGHT/HEIGHT);
	}
	else{
		SDL_SetWindowSize(window, 320, 200);
		SDL_RenderSetScale(renderer, 1, 1);
	}
}
