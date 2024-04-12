int WireRead( int _Address,byte _DATA ){
  Wire.beginTransmission(_Address>>1);
  Wire.write(_DATA);  
  Wire.endTransmission(true);
  Wire.requestFrom(_Address>>1,1);
  if(Wire.available()>0){
    return Wire.read();
  }
}

int WireRead2( int _Address,byte _DATA0, byte _DATA1 ){
  Wire.beginTransmission(_Address>>1);
  Wire.write(_DATA0);  
  Wire.write(_DATA1);
  Wire.endTransmission(true);
  Wire.requestFrom(_Address>>1,2);
  if(Wire.available()>0){
    int data0 = Wire.read();
    int data1 = Wire.read()<<8;
    return data1+data0;
  }
}

void WireWrite( int _Address, byte _DATA, byte _canShu ){
  Wire.beginTransmission(_Address>>1);
  Wire.write(_DATA);
  Wire.write(_canShu);
  Wire.endTransmission(true);
}
