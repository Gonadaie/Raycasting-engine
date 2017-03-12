# Raycasting-engine
A small old school style raycasting engine made with C++, SDL2 and MinGW.
I used Atom as my editor.

This project is far from perfect, it is not even good but it was great for learning how things work.
There are many optimisations to do

It use txt files for map loading. Each map cell is made of 4 digits, the first indicate the type of that cell :
0 - None
1 - Wall
More to come...

The next 3 digits are the texture code. At the moment, there's only one texture (1 for a wall)

--- CONTROLS ---
Up arrow : Move forward
Down arrow : Move backward
Right arrow : Turn right
Left arrow : Turn left
Left alt + right arrow or left arrow : Strafe right or left

There's not collision detection at the moment.
You can change the game resolution by editing the WIDTH and HEIGHT constants in the constants.cpp file.
If you set a resolution lower than your screen resolution, you can force the fullscreen mode by uncommenting the setFullscreen() function in the main.cpp file. It's a bit clunky though

Sorry for my bad english :)
