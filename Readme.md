# 可穿戴体感控制手套
## 材料
一块arduino micro（必须是micro，只有32U4的芯片才可以用Mouse函数，，mini nano都不行）

一块ADXL345传感器模块

两根可弯曲传感器

一个电位器用于校准

一些面板线和一块面包板，订书钉，皮筋等

一只手套，和将传感器缝在手套上的线

## 资料
ADXL345_cn.pdf 是ADXL345数据手册
ADXL345_sch.pdf 是ADXL345电路图
注意要购买支持5V的模块，否则要买5V转3.3V的变压器

![Arduino Micro引脚图](https://github.com/JasonJarvan/Hand-Motion-Recognize-Wearable-Device/blob/main/Arduino%20Mirco%E5%BC%95%E8%84%9A%E5%9B%BEpng.png)

## 线路

![传感器走线图](https://github.com/JasonJarvan/Hand-Motion-Recognize-Wearable-Device/blob/main/%E4%BC%A0%E6%84%9F%E5%99%A8%E8%B5%B0%E7%BA%BF%E5%9B%BE.jpg)

![可弯曲传感器走线图](https://github.com/JasonJarvan/Hand-Motion-Recognize-Wearable-Device/blob/main/%E5%8F%AF%E5%BC%AF%E6%9B%B2%E4%BC%A0%E6%84%9F%E5%99%A8%E8%B5%B0%E7%BA%BF%E5%9B%BE.jpg)

## 源码
安装Arduino

源码/MouseWheel和MousePress放入arduino-1.5.7\libraries

源码/calibration_ADXL345 中的calibration_ADXL345.ino打开，用于校准

校准完成后，将源码/air_mouse 中的air_mouse.ino 打开，把刚才校准后的数据写入air_mouse中setup()方法的如下两行，就是后面那个B00110010和B00000000：

```c++
  WireWrite( ADXAddressR, OFSX,B00110010 );//50左手
  WireWrite( ADXAddressR, OFSY,B00000000 );//0左手
```

setup函数：
```c++
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
```

最后把这个air_mouse传到arduino上就可以了。

实现视频如 ![传感器鼠标功能测试](https://github.com/JasonJarvan/Hand-Motion-Recognize-Wearable-Device/blob/main/%E4%BC%A0%E6%84%9F%E5%99%A8%E9%BC%A0%E6%A0%87%E5%8A%9F%E8%83%BD%E6%B5%8B%E8%AF%95.mp4)
