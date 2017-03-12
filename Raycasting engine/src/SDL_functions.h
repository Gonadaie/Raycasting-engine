#ifndef _SDL_FUNCTIONS_
#define _SDL_FUNCTIONS_

bool initSDL();
bool createWindow(SDL_Window** window, const unsigned int width, const unsigned int height);
void setFullScreen(SDL_Window* window, SDL_Renderer* renderer, bool b);

#endif
