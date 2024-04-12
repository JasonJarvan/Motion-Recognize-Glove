#include <Arduino.h>
#include "mousePress.h"


MousePress::MousePress( const byte mouse_pin, const byte mouse_button ){
  _mouse_pin = mouse_pin;
  _mouse_button = mouse_button;
  _clickTime = millis();
  _clickTimeOld = millis();
  Mouse.begin();
  Serial.begin(9600);
  pinMode( _mouse_pin, INPUT_PULLUP );
}

void MousePress::press_mouse(){
  pressButton(_mouse_pin,_mouse_button);
}

boolean MousePress::pressButton( byte _buttonPin ,byte _mouseButton ){
  boolean _pressValue = !digitalRead( _buttonPin ),
          _pressTrue = xiaoDou( _pressValue );
  if( _pressValue && _pressTrue && !Mouse.isPressed(_mouseButton) ) {
    Mouse.press( _mouseButton );
    Serial.println( "mouse is press" );
  }else if( !_pressValue && !_pressTrue && Mouse.isPressed(_mouseButton) ){
    Mouse.release( _mouseButton );
    Serial.println( "mouse no press" );
  }
}


boolean MousePress::xiaoDou( const boolean _pressValue ){
  boolean _pressValueOld ;          
  if( millis() - _clickTimeOld > 1 ){
    _pressValueOld = _pressValue;
    _clickTimeOld = millis();
  }  
  if( (_pressValue != _pressValueOld) && !_pressBegin ){
    _clickTime = millis();
    _pressBegin = true;
  }
  if( millis() - _clickTime > 10 && _pressBegin ){ 
    if( _pressValue ){
      _pressBegin = false;
      return true;
    }else{
      _pressBegin = false;
      return false;
    }
  }    
}
