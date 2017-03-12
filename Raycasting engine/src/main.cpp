#include <iostream>
#include <SDL.h>
#include "SDL_functions.h"
#include "Game.h"
#include "constants.h"

using namespace std;

int main(int argc, char* args[]){

	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Renderer* renderer = NULL;

	if(!initSDL()){
		exit(-1);
	}
	else{
		createWindow(&window, WIDTH, HEIGHT);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		//setFullScreen(window, renderer, true);
		Game game = Game(renderer);
		game.run();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
