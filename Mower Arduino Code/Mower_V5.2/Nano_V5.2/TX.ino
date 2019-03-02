 
void TX_Volts()  {  
  mySerial.print(VoltsTX);
  mySerial.println("\j");
  Serial.print("VoltsTX = ");
  Serial.print(VoltsTX);
}

void TX_Amps()  {
  mySerial.print(AmpsTX);
  mySerial.println("\q");
  Serial.print(" / ");
  Serial.print("AmpsTX = ");
  Serial.println (AmpsTX);
}
