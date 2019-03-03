#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11);  // RX, TX

//Amp Sensor Variables.
int RawValueAmp= 0;
int RawValueVolt = 0;


// Transmission of the raw sensor values to the Arduino MEGA
float AmpsTX; 
float VoltsTX;
bool Test;


void setup(){ 
 Serial.begin(9600);
 mySerial.begin(9600);
 Test = 0;

 if (Test == 1) {
  RawValueAmp = 510;
  RawValueVolt = 500;
 }
}

void loop(){

 //Read Amp and Volt Raw Number Sensor Values 
 if (Test == 0) { 
 RawValueAmp = analogRead(A1);
 RawValueVolt = analogRead(A2);
 }

  if (Test == 1 )   {
 RawValueAmp = RawValueAmp + 1;
 if (RawValueAmp > 550) RawValueAmp = 500;
 RawValueVolt = RawValueVolt + 1;
 if (RawValueVolt > 550) RawValueVolt = 500;
  }


 Serial.print("VoltsTX Raw = ");
 Serial.print(RawValueVolt);
 Serial.print(" / ");
 Serial.print("AmpsTX Raw = ");
 Serial.println (RawValueAmp);

   
 Calculate();
 TX_Volts();
 delay(5);
 TX_Amps();
    
} 
