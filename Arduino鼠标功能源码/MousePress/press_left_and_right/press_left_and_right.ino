#include <mousePress.h>
const byte LEFT_BUTTON = 5;
const byte RIGHT_BUTTON = 4;

MousePress myMouseLeft( LEFT_BUTTON, 1 );
MousePress myMouseRight( RIGHT_BUTTON, 2 );
void setup() {
  pinMode( 10,INPUT_PULLUP );
}

void loop() {
  if( !digitalRead(10)){
    Serial.println("MOUSE IS END");
    Mouse.end();
    delay(1000);
  }
  myMouseLeft.press_mouse();
  myMouseRight.press_mouse();
  
}
