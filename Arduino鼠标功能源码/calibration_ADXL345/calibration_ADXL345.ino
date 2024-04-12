//这个程序用来校准ADXL345，需要外接一个电位器
#include <Wire.h>  //调用arduino自带的I2C库
#define DEVID           0x00  //只读
#define THRESH_TAP      0x1D
#define OFSX            0x1E
#define OFSY            0x1F
#define OFSZ            0x20
#define DUR             0x21
#define Latent          0x22
#define Window          0x23
#define THRESH_ACT      0x24
#define THRESH_INACT    0x25
#define TIME_INACT      0x26
#define ACT_INACT_CTL   0x27
#define THRESH_FF       0x28
#define TIME_FF         0x29
#define TAP_AXES        0x2A  //B00000111
#define ACT_TAP_STATUS  0x2B  //只读
#define BW_RATE         0x2C  //B00001011
#define POWER_CTL       0x2D  //B00001000
#define INT_ENABLE      0x2E
#define INT_MAP         0x2F
#define INT_SOURCE      0x30
#define DATA_FORMAT     0x31  //B00001000
#define DATAX0          0x32  //只读
#define DATAX1          0x33  //只读
#define DATAY0          0x34  //只读
#define DATAY1          0x35  //只读
#define DATAZ0          0x36  //只读
#define DATAZ1          0x37  //只读
#define FIFO_CTL        0x38
#define FIFO_STATUS     0x39
#define ADXAddressR     0xA7
#define ADXAddressW     0xA6
double X,Y,Z;
unsigned long Time;
int A0read;
void setup(){
  Wire.begin();  //初始化I2C
  Serial.begin( 9600 );
  pinMode( 10, INPUT_PULLUP );
  pinMode( 9, INPUT_PULLUP );
  pinMode( 8, INPUT_PULLUP );
  Time = millis();
  WireWrite( ADXAddressR, POWER_CTL,B00001000 );
  WireWrite( ADXAddressR, THRESH_TAP,B00000000 );
  WireWrite( ADXAddressR, OFSX,B00000101 );
  WireWrite( ADXAddressR, OFSY,B11100001 );
  WireWrite( ADXAddressR, OFSZ,B00000000 );
  WireWrite( ADXAddressR, DUR,B00000000 );
  WireWrite( ADXAddressR, Latent,B00000000 );
  WireWrite( ADXAddressR, Window,B00000000 );
  WireWrite( ADXAddressR, THRESH_ACT,B00000000 );
  WireWrite( ADXAddressR, THRESH_INACT,B00000000 );
  WireWrite( ADXAddressR, TIME_INACT,B00000000 );
  WireWrite( ADXAddressR, ACT_INACT_CTL,B00000000 );
  WireWrite( ADXAddressR, THRESH_FF,B00000000 );
  WireWrite( ADXAddressR, TIME_FF,B00000000 );
  WireWrite( ADXAddressR, TAP_AXES,B00000000 );
  WireWrite( ADXAddressR, BW_RATE,B00001010 );
  WireWrite( ADXAddressR, INT_ENABLE,B00000000 );
  WireWrite( ADXAddressR, INT_MAP,B00000000 );
  WireWrite( ADXAddressR, DATA_FORMAT,B00001000 );
  WireWrite( ADXAddressR, FIFO_CTL,B00000000 );
}

void loop(){
//--------------读取数据---------------------//
  X = WireRead2( ADXAddressR, DATAX0,DATAX1);
  Y = WireRead2( ADXAddressR, DATAY0,DATAY1);
  Z = WireRead2( ADXAddressR, DATAZ0,DATAZ1);

//----------偏移校准----------------------------//

  if( millis() - Time > 500 ){
    Serial.print("X :");
    Serial.println( X/256.00 );
    Serial.println(WireRead( ADXAddressR, OFSX ));
    Serial.print("Y :");
    Serial.println( Y/256.00 );
    Serial.println(WireRead( ADXAddressR, OFSY ));
    //----calibrationXYZ()函数的 第一个参数是读取哪个轴（char型），
    //第二个参数是控制用的输入引脚（int型）-----//
    //将电位器的中间脚接A0
    //将要校准的轴的控制引脚接地，然后转动电位器，就能校准
    calibrationXYZ( 'X',10 ); //10引脚接地为校准X轴
    calibrationXYZ( 'Y',9 );//9引脚接地为校准Y轴
    calibrationXYZ( 'Z',8 ); //8引脚接地为校准Z轴
    //(ps:因为我的Z轴是坏的所以我也就没有用到Z轴)
    Time = millis();
  }
  //----------偏移校准----------------------------//
}

