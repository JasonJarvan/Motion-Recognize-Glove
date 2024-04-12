 void speedo(){   //太好了通过计算可以用了2015/2/17
    speedoPWMX = speedoX-(speedoX/100*100);
    speedoPWMY = speedoY-(speedoY/100*100);
    if( speedoPWMX == 0 ){
      speedoxVal = speedoX/100;
    }else{
      speedoxVal = speedoX/100 + 1;
    }
    if( speedoPWMY == 0 ){
      speedoyPos = speedoY/100;
    }else{
      speedoyPos = speedoY/100 + 1;
    }
    PWMGOX = speedoPWMX/speedoxVal + (speedoxVal-1)*100/speedoxVal;
    PWMGOY = speedoPWMY/speedoyPos + (speedoyPos-1)*100/speedoyPos;
    //*100要放在前面，否则会计算错误，因为int型变量做除法时会损失精度
    PWMSTOPX = 100 - PWMGOX;
    PWMSTOPY = 100 - PWMGOY;
 }
