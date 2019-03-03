/* Main Battery Voltage Test
************************************************************************************/

/* ADCMan function (needed for Perimeter Wire readings) doesnt allow direct reading of Analog pins which makes this simple operation a little complicated*/
void TestforBatteryVoltage()   {
  Check_Serial_Communication_Volts();  
  // ask the Nano for Voltage and Amps reading
   
  if ((Nano_Data_Volt_Received == 1) && (VoltsTX < 15) && (VoltsTX > 7)) {
    BatteryVoltage_Last = VoltsTX;
    }


  else {
    Serial.println(F("Using previous values for Volts and Amps"));
    VoltsTX = BatteryVoltage_Last;
    Serial.print(F("VoltsTX Last = "));
    Serial.println(VoltsTX);
    Serial.println(F("- - - - - - - - - - - - - - - - - - - - - - - "));
    }

           
    lcd.setCursor(10, 0);
    lcd.print("V:");
    lcd.setCursor(12, 0);    
    lcd.print(VoltsTX);  

}

void Action_For_Battery_Voltage() {

//  Logic for how the battery readings should be handled

    // Checks if the battery is not connected by a voltage under 6V
    if (VoltsTX < 10) {
      Battery_NoBattery_Found = (Battery_NoBattery_Found + 1);
      Serial.print(F("####### No Battery Found Reading ###### : "));
      Serial.println(Battery_NoBattery_Found);
      }
    
    if (VoltsTX < BatteryMin) {
      Battery_To_Charge_Station_Count = (Battery_To_Charge_Station_Count + 1);
      Serial.print(F("####### Battery needs charging reading ######## : "));
      Serial.println(Battery_To_Charge_Station_Count);
      }

      if (VoltsTX >= BatteryMin) {
      Serial.print(F("Battery >"));
      Serial.println(BatteryMin);
      Battery_To_Charge_Station_Count = 0;
      Battery_NoBattery_Found = 0;
      }
  

// Handles how the voltage is printed to the LCD display and what the mower does.
    if ( (BatteryVoltage > 10 ) && (BatteryVoltage <= BatteryMin) && (Battery_To_Charge_Station_Count > 10) ){
       //MowerMotionStatus = 1;
       lcd.setCursor(0, 1);
       lcd.print("Battery < :  ");
       lcd.print(BatteryMin);
       Serial.print(F("Battery below : "));
       Serial.println(BatteryMin);
       }
  


    // Checks if a series of low voltage signals have been detected i.e. the mower wont be sent to the charger due to just 1 bad signal
    if (Battery_To_Charge_Station_Count > 20)  {
      Motion_StopMotors();
      StopSpinBlades();
      MowerMotionStatus = 1;
      Error = 7;
      Serial.print(F("Batt Sensor - Battery Empty < "));
      Serial.println(BatteryMin);                               //sets Mower Motion to 1 which is all stop
      lcd.setCursor(0, 1);
      lcd.print("Mower -> Charger");
      delay(5000);
      }

    if ((BatteryVoltage <= 10) && (Battery_NoBattery_Found >= 5)){
       lcd.setCursor(10, 0);
       lcd.print("V:");
       lcd.setCursor(12, 0);    
       lcd.print("OFF ");     
       }
  
   
  Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
}






void Check_Serial_Communication_Volts (){
        Nano_Data_Volt_Received = 0;
        Serial.println(F("- - - - - - - - - - - - - - - - - - - - - - - - - - - -"));
        Serial.println(F("Recieving Data from NANO"));
        VoltsTX = Serial1.parseFloat();
        if(Serial1.read()== '\j'){
            Serial.print(F("VoltTX Nano : "));
            Serial.println(VoltsTX);
            Nano_Data_Volt_Received = 1;
            Serial.println(F("- - - - - - - - - - - - - - - - - - Y Y "));
            }
        if ( Nano_Data_Volt_Received == 0 ) {
            Serial.println(F("No Volt Data received from Nano"));
            }
}


void Check_Serial_Communication_Amps (){
        Nano_Data_Amp_Received = 0; 
        Serial.println(F("- - - - - - - - - - - - - - - - - - - - - - "));
        AmpsTX = Serial1.parseFloat();
        if(Serial1.read()== '\q'){
            Serial.print(F("AmpTX Nano : "));
            Serial.println(AmpsTX);  
            Nano_Data_Amp_Received = 1;
            }
        if ( Nano_Data_Amp_Received == 0 ) {
           Serial.println(F("No AMP Data received from Nano"));
           }
        Serial.println(F("- - - - - - - - - - - - - - - - - - - - -  "));
    }


// checks to see if the mower is on the charging station
void Check_if_Docked () {

  Check_Serial_Communication_Amps();                            // Reads the AMPs sensor from the Arduino Nano
  if ((AmpsTX >= 0.6) && (AmpsTX <=4) ){                       // if Amps are between this there is a charge detected.  Amps above 4 are discounted as a miscommunication
    delay(1000);
    Serial.println(F("Charging Current detected"));
    Serial.print(F("Amps : "));
    Serial.println(AmpsTX);
    Motion_StopMotors();    
    Serial.println(F("Mower Docked"));
    lcd.print("Docked in");
    lcd.setCursor(0, 1);
    lcd.print("Charging Station");                                // Prints info to LCD display
    delay(2000);
    Power_Down_Mower();                                           // Shits down the Mower ready for charging and mowing again.
    lcd.clear();
  }
  if (AmpsTX >= 4) {                                            // if Amps are above 4A then something is miscommunicating with the Nano and its discounted.
      lcd.setCursor(15, 1);                                       // displays a # briefly ón the LCD to show it happened and was discounted
      lcd.print("#");
      Serial.println();
      Serial.println(F("Error - Too many Amps for docking station...."));
      Serial.println();
      }
  if (AmpsTX < 0.6) {
    Serial.print(F("Not Docked"));
    lcd.setCursor(15, 1);
    lcd.print(" ");
  }

}


void Check_if_Charging() {
    
    if ((AmpsTX > 0.6) && (AmpsTX < 4) ) {
      lcd.setCursor(0,0);            // Spaces to the right & down
      lcd.print("Amp:");
      lcd.print(AmpsTX);
      }
    if (AmpsTX < 0.6) {
      lcd.setCursor(0,0);            // Spaces to the right & down
      lcd.print("        ");
      }

  }
