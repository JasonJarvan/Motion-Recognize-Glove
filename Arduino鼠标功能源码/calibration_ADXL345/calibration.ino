  void calibrationXYZ( char _axis,int _pin ){
    switch ( _axis ){
      case 'X':
        Serial.print( "X =" );
        Serial.println(X/256.00);
        if( !digitalRead( _pin )){
          A0read = map(analogRead( A0 ),0,1023,0,255);
          WireWrite( ADXAddressR, OFSX,A0read );
          Serial.print("OFS X :");
          Serial.println(WireRead( ADXAddressR, OFSX ));
        }
        break;
      case 'Y':
        Serial.print( "Y =" );
        Serial.println(Y/256.00);
        if( !digitalRead( _pin )){
          A0read = map(analogRead( A0 ),0,1023,0,255);
          WireWrite( ADXAddressR, OFSY,A0read );
          Serial.print("OFS Y :");
          Serial.println(WireRead( ADXAddressR, OFSY ));
        }
        break;
      case 'Z':
        Serial.print( "Z =" );
        Serial.println(Z/256.00);
        if( !digitalRead( _pin )){
          A0read = map(analogRead( A0 ),0,1023,0,255);
          WireWrite( ADXAddressR, OFSZ,A0read );
          Serial.print("OFS Z :");
          Serial.println(WireRead( ADXAddressR, OFSZ ));
        }
        break;
    }
  }
