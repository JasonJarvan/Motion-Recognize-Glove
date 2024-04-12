#ifndef __MOUSEWHEEL_H__
#define __MOUSEWHEEL_H__
#include "Arduino.h"

class MouseWheel{
  public:
    MouseWheel( const byte A_pin, const byte B_pin);
    byte read_wheel();
  private:
    byte _A_pin,_B_pin;
    boolean _wheelA,_wheelB,_wheelAold;
};
#endif
