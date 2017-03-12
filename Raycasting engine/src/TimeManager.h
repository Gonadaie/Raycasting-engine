#ifndef _TIMEMANAGER_
#define _TIMEMANAGER_

extern const double SEC;
extern double deltaTime;
extern unsigned int fps;

class TimeManager{

public:
  TimeManager();
  void update();

private:
  double before;
  double after;
  double elapsed;
  unsigned int ticks;
};

#endif
