#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

class InputHandler{

public:
  InputHandler();
  ~InputHandler();
  bool isKeyPressed(int keyCode);
  void setKeyPressed(int keyCode, bool pressed);

private:
  bool* keys;
};

#endif
