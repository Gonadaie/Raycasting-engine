#OBJS specifies which files to compile as part of the project
OBJS = main.cpp SDL_functions.cpp Game.cpp Map.cpp Entity.cpp Player.cpp InputHandler.cpp TimeManager.cpp constants.cpp trigo_functions.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = rce

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -IC:\mingw_dev_lib\SDL2\include\SDL2 -IC:\mingw_dev_lib\SDL_Image\include\SDL2 -LC:\mingw_dev_lib\SDL2\lib -LC:\mingw_dev_lib\SDL_Image\lib -w -Wl, -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -o $(OBJ_NAME)
