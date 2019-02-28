#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11);  // RX, TX

//Amp Sensor Variables.
int RawValueAmp= 0;
int RawValueVolt = 0;


// Transmission of the raw sensor values to the Arduino MEGA
char str[4];
int AmpsTX; 
int VoltsTX;


void setup(){ 
 Serial.begin(9600);
 mySerial.begin(9600);
}

void loop(){

 //Read Amp and Volt Raw Number Sensor Values 
 AmpsTX = analogRead(A1);
 VoltsTX = analogRead(A2);

// Transmit Values of AmpsTX and VoltsTX 
 if (mySerial.read() == '*')
  { 
    mySerial.write(highByte(AmpsTX));
    mySerial.write(lowByte(AmpsTX));
    delay(8);
  }

 if (mySerial.read() == '~')
  { 
    mySerial.write(highByte(VoltsTX));
    mySerial.write(lowByte(VoltsTX));
    delay(8);
  }

Serial.print("AmpsTX = ");
Serial.print(AmpsTX);
Serial.print(" / ");
Serial.print("VoltsTX = ");
Serial.println(VoltsTX);
    
} 



