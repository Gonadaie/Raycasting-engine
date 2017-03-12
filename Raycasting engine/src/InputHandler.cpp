#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(){
  keys = new bool[256];
}

InputHandler::~InputHandler(){
  delete[] keys;
  keys = NULL;
}

bool InputHandler::isKeyPressed(int keyCode){
  if(0 < keyCode && keyCode < 256)
    return keys[keyCode];
  else
    return false;
}

void InputHandler::setKeyPressed(int keyCode, bool pressed){
  if(0 < keyCode && keyCode < 256)
    keys[keyCode] = pressed;
}
