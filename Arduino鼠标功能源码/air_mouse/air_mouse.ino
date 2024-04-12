#include <mousePress.h>
#include <mouseWheel.h>
const byte LEFT_BUTTON = 5;
const byte RIGHT_BUTTON = 4;
const byte CLICK = 6;
const byte END = 10;
int clickSpeedo = 200;
MousePress myMouseLeft( LEFT_BUTTON, 1 );
MousePress myMouseRight( RIGHT_BUTTON, 2 );
MouseWheel mywheel(9,8);
/**-------------------使用ADXL345制作体感控制鼠标-----------------**/
#include <Wire.h>
/*------------------------ADXL345寄存器地址----------------------*/
#define DEVID           0x00  //只读==291
#define OFSX            0x1E//B00000101
#define OFSY            0x1F//B11100001
#define BW_RATE         0x2C  //设置为B00001011
#define POWER_CTL       0x2D  //设置为B00001000
#define DATA_FORMAT     0x31  //设置为B01000000
#define DATAX0          0x32  //只读
#define DATAX1          0x33  //只读
#define DATAY0          0x34  //只读
#define DATAY1          0x35  //只读
#define DATAZ0          0x36  //只读
#define DATAZ1          0x37  //只读
#define ADXAddressR     0xA7

/*----------------------控制鼠标指针方向和加速度---------------*/
boolean up,down,left,right;
byte x=0,y=0,xVal=0,yPos=0,wheel=0;
int x345,y345,x345old,y345old,
    value345X = 30,value345Y = 30; //倾斜阈值
int inclineX = 0, inclineY = 0,
    speedoX,speedoY,//用来控制Mouse.move（）函数XY值,
    speedoxVal,speedoyPos,     //incline是用ADXL345的倾斜度
    speedoPWMX,speedoPWMY,
    PWMGOX, PWMSTOPX,
    PWMGOY, PWMSTOPY;         
//int accelerationX = 1,accelerationY = 1,//越大，速度越快
//    accelerationValue = 4;//加速度阈值
//boolean valueAcceleration = true;   //控制acceleration产生加速度
//unsigned long ctrlAccelerationTime = 0;   //用来控制acceleration的时间变量，用来给鼠标产生加速度
boolean valuePWMX = true,valuePWMY = false;   
//PWM控制鼠标速度的一个控制变量,用来切换鼠标“走”和“停”
unsigned long ctrlMouseTimeX = 0,ctrlMouseTimeY = 0;  //PWM控制鼠标速度的一个控制变量
unsigned long startTime = 0,
              clickTime = 0;
void setup() {
  Wire.begin();  //初始化I2C
  Serial.begin( 9600 );
  Mouse.begin();
  Keyboard.begin();
  WireWrite( ADXAddressR, DATA_FORMAT,B00001000 );
  WireWrite( ADXAddressR, POWER_CTL,B00001000 );
  WireWrite( ADXAddressR, BW_RATE,B00001011 );
  WireWrite( ADXAddressR, OFSX,B00110010 );//50左手
  WireWrite( ADXAddressR, OFSY,B00000000 );//0左手
  ctrlMouseTimeX = micros();
  ctrlMouseTimeY = micros();
  //ctrlAccelerationTime = millis();
  clickTime = millis();
  startTime = millis();
  pinMode( END, INPUT_PULLUP );
  pinMode( CLICK, INPUT_PULLUP );
}

void loop() {
  if( micros() > 4294967295-10000 ){//防止micros()溢出
    ctrlMouseTimeX = micros();
    ctrlMouseTimeY = micros();
    Serial.println("reset");
  }else{
  if( !digitalRead(END) ){//END接地，airmouse失效
    Mouse.end();
    delay(1000);
  }else{
//----------读取ADXL345的XY值----------------//  
  y345 = -WireRead2( ADXAddressR, DATAX0,DATAX1);
  x345 = WireRead2( ADXAddressR, DATAY0,DATAY1);  
  if(x345<0)
    x345*=1.5;
  if(y345>0)
    y345*=1.5;
  speedoX = constrain(pow(abs(x345),2)/100,0,12700);
  speedoY = constrain(pow(abs(y345),2)/100,0,12700);
  speedo();  //通过speedo将倾角计算成xval ypos 和PWM 
 // 2015/2/16 2015/2/17*************************
 //------------判断上下左右---------------------//
  if( x345 > value345X ){
    x = -speedoxVal;
  }else if( x345 < -value345X ){
    x = speedoxVal;
  }else
    x = 0;
  if( y345 > value345Y ){
    y = -speedoyPos;
  }else if( y345 < -value345Y ){
    y = speedoyPos;
  }else
    y = 0;   
//左键右键连击
  myMouseLeft.press_mouse();
  myMouseRight.press_mouse();
  wheel = mywheel.read_wheel();
  if( millis() - clickTime > clickSpeedo ){
    if(!digitalRead(CLICK))
      Mouse.click();
    clickTime = millis();
  }
  
////----------串口监视器显示ADXL345的XY值----------------// 
  if( millis() - startTime > 200 ){
    Serial.print( "  X = " );
    Serial.print( x345 );
    Serial.print( "  Y = " );
    Serial.println( y345 );
    Serial.print( "  speedoX = " );
    Serial.print( speedoX );
    Serial.print( "  speedoY = " );
    Serial.println( speedoY );
//    Serial.print( "  accelerationX = " );
//    Serial.print( accelerationX );
//    Serial.print( "  accelerationY = " );
//    Serial.println( accelerationY );   
    startTime = millis();
  }


//------------PWM控制鼠标速度----------------//
  if( (micros() - ctrlMouseTimeX >= PWMSTOPX*80)//“停”
      && valuePWMX == true){
    ctrlMouseTimeX = micros();
    valuePWMX = !valuePWMX;
    xVal = x;
  }else if ( (micros() - ctrlMouseTimeX >= PWMGOX *80)//“走”
             && valuePWMX == false ){
    ctrlMouseTimeX = micros();
    valuePWMX = !valuePWMX;
    xVal = 0;
  }
  if( (micros() - ctrlMouseTimeY >= PWMSTOPY*80) //“停”
      && valuePWMY == true){
    ctrlMouseTimeY = micros();
    valuePWMY = !valuePWMY;
    yPos = y;
  }else if ( (micros() - ctrlMouseTimeY >= PWMGOY *80)//“走”
             && valuePWMY == false ){
    ctrlMouseTimeY = micros();
    valuePWMY = !valuePWMY;
    yPos = 0;
  }
//----------最后是控制鼠标的函数---------//
  Mouse.move( xVal ,yPos ,wheel );

//------------计算加速度----------//  
//  if( millis() - ctrlAccelerationTime > 10){ 
//    if( valueAcceleration ){//每隔10毫秒记录一次old
//      x345old = x345;
//      y345old = y345;
//      valueAcceleration = !valueAcceleration;
//    }else if ( valueAcceleration == false ){//每隔10毫秒计算一次加速度
//      accelerationX = abs(x345 - x345old);
//      accelerationY = abs(y345 - y345old);
////      if( accelerationX <2 )
////        accelerationX = 2;
////      if( accelerationY <2 )
////        accelerationY = 2;
////      if( accelerationX >5)
////        accelerationX = 5;
////      if( accelerationY >5)
////        accelerationY = 5;
//      valueAcceleration = !valueAcceleration;
//    }
//    ctrlAccelerationTime = millis();
//  }

  }
  }
}
