//测试成功2015/2/19
#include <mouseWheel.h>
MouseWheel mywheel(9,8);
void setup() {
  Mouse.begin();
  pinMode(10,INPUT_PULLUP);
}

void loop() {
  if( digitalRead(10)){
  Mouse.move(0,0,mywheel.read_wheel());
  delay(3);
  }
}
