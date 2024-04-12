#include <Arduino.h>
#include "mouseWheel.h"

MouseWheel::MouseWheel( const byte A_pin, const byte B_pin){
  _A_pin = A_pin;
  _B_pin = B_pin;
  pinMode(_A_pin,INPUT_PULLUP);
  pinMode(_B_pin,INPUT_PULLUP);
}
byte MouseWheel::read_wheel(){
  _wheelA = digitalRead(_A_pin);
  _wheelB = digitalRead(_B_pin);
  if( _wheelA && !_wheelAold){
    if( _wheelB ){
      _wheelAold = _wheelA;
      return 1;
    }else if( !_wheelB ){
      _wheelAold = _wheelA;
      return -1;
    }
  }else if( !_wheelA && _wheelAold ){
    if( !_wheelB ){
      _wheelAold = _wheelA;
      return 1;
    }else if( _wheelB ){
      _wheelAold = _wheelA;
      return -1;
    }
  }else{
    return 0;    
  }
}
