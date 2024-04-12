#ifndef __MOUSEPRESS_H__
#define __MOUSEPRESS_H__
#include "Arduino.h"

  class MousePress{
    public:
      MousePress( const byte mouse_pin,const byte mouse_button );
      void press_mouse();
    private:
      boolean pressButton( byte _buttonPin , byte _mouseButton ); 
      boolean xiaoDou( const boolean _pressValue );
      
      byte _mouse_pin;
      byte _mouse_button;
      boolean _pressBegin;
      unsigned long _clickTime,_clickTimeOld;
//      boolean _pressValue,_pressTrue;
//      boolean _pressValueOld ;
  };
#endif
