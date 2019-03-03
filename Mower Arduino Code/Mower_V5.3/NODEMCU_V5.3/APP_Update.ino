



void Update_Blynk_App_With_Status() {
    if (RX_Data_Recieved == 1)  {               // checks that data has been received


        //Mower is Mowing
        if (MowerMotionStatus < 151)  {        
         Blynk.virtualWrite(V5, MowerMotionStatus);     // update Loops Label
         
          if ((MowerMotionStatus > 2) && (MowerMotionStatus < 5)) {
          lcd.clear();
          lcd.print(0, 0, "Start Mow. ");   // Print to APP LCD
          Blynk.virtualWrite(V7, 1023);     // Mow LED ON
          Blynk.virtualWrite(V8, 0);        // V8 Docked LED OFF
          Blynk.virtualWrite(V2, LOW);      // Stop Button OFF
          Blynk.virtualWrite(V9, 0);        // TrackingLED OFF
          Blynk.virtualWrite(V0, HIGH);     // Mowing Button ON
          Blynk.virtualWrite(V10, LOW);     // Dock Button Off
          Blynk.virtualWrite(V11, 0);       // Compass LED OFF
          }
         if (MowerMotionStatus > 30) {
          lcd.clear();
          lcd.print(0, 0, "Mowing . ");    // Print to APP LCD
          }
         if (MowerMotionStatus > 60) {
          lcd.clear();
          lcd.print(0, 0, "Mowing . . ");    // Print to APP LCD
          }
        }

        //Mower is Docked
        if (Docked == 1) {                    // if the mower is docked then
          Blynk.virtualWrite(V8, 1023);       // Docked LED ON
          Blynk.virtualWrite(V0, LOW);          // Mowing Button OFF
          Blynk.virtualWrite(V2, HIGH);       // Stop ON
          Blynk.virtualWrite(V1, LOW);        // Go To DOck Off
          Blynk.virtualWrite(V10, LOW);       // Dock Off
          Blynk.virtualWrite(V7, 0);          // Mow LED OFF
          Blynk.virtualWrite(V9, 0);          // TrackingLED OFF
          lcd.clear();
          lcd.print(0, 0, "Docked");          // Print to APP LCD
        }        

        
        //Mower is tracking to Garden
        if ((MowerMotionStatus == 0) && (Docked == 0) && (Mower_Stopped == 0) && (Error == 0) ){
          lcd.clear();
          lcd.print(0, 0, "Tracking");      // Print to APP LCD
          Blynk.virtualWrite(V7, 0);        // Mowing LED OFF
          Blynk.virtualWrite(V8, 0);        // Docked LED ON
          Blynk.virtualWrite(V2, LOW);      // Stop Button ON
          Blynk.virtualWrite(V9, 1023);     // Tracking LED ON
          Blynk.virtualWrite(V10, HIGH);    // Dock Button ON
          Blynk.virtualWrite(V11, 0);       // Compass LED OFF
          
          }

               
        //Mower is tracking to Docking Station
        if ((MowerMotionStatus == 0) && (Docked == 0) && (Mower_Stopped == 0) && (Error ==7 ) ){
          lcd.clear();
          lcd.print(0, 0, "Tracking");      // Print to APP LCD
          Blynk.virtualWrite(V7, 0);        // Mowing LED OFF
          Blynk.virtualWrite(V8, 0);        // Docked LED OFF
          Blynk.virtualWrite(V2, LOW);      // Stop ON
          Blynk.virtualWrite(V9, 1023);     // Tracking LED ON
          Blynk.virtualWrite(V11, 1023);    // Compass LED ON
          Blynk.virtualWrite(V10, LOW);     // Dock Button Off
          Blynk.virtualWrite(V1, HIGH);     // Go to Dock Button ON
          Blynk.virtualWrite(V0, LOW);      // Mowing Button OFF
          
          }
        
        //Mower is in a stopped condition
        if ((MowerMotionStatus == 0) && (Docked == 0) && (Mower_Stopped == 1) ){
          lcd.clear();
          lcd.print(0, 0, "Mower Stopped"); // Print to APP LCD
          Blynk.virtualWrite(V7, 0);        // Mowing LED OFF
          Blynk.virtualWrite(V8, 0);        // Docked LED ON
          Blynk.virtualWrite(V2, HIGH);     // Stop ON
          Blynk.virtualWrite(V9, 0);        // Tracking LED ON
          Blynk.virtualWrite(V0, LOW);      // Mowing Button OFF
          Blynk.virtualWrite(V11, 0);       // Compass LED OFF
          
          }
      
   }
   if (RX_Data_Recieved == 0 ) Serial.println("Data not received");
}


BLYNK_WRITE(V0)       // Quick Start Mowing Function
{
  Clear_APP(); 
  
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 1) StartMower();       
  //Clear_APP();      
  lcd.clear();
  lcd.print(0, 0, "Starting . . ");      // Print to APP LCD
  delay(100);
  Blynk.virtualWrite(V0, HIGH);   // Start Mowing Buton ON

}


BLYNK_WRITE(V1)      // Go to Docking Station
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 1) Going_Home();
  //Clear_APP();
  lcd.clear();
  lcd.print(0, 0, "Docking . . ");        // Print to APP LCD
  delay(100);
  Blynk.virtualWrite(V1, HIGH);           // Docking Button ON

}



BLYNK_WRITE(V2)      // Pause Mower Function
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  if (pinValue == 1)  Pause_Mower();
  //Clear_APP();
  lcd.clear();
  lcd.print(0, 0, "Stopping . . ");       // Print to APP LCD
  delay(100);
  Blynk.virtualWrite(V2, HIGH);           // Pause Button ON
   }





BLYNK_WRITE(V10)      // Exit Dock Function
{
  int pinValue = param.asInt(); // assigning incoming value from pin V10 to a variable
  if (pinValue == 1) Exit_Dock();
  //Clear_APP();
  lcd.clear();
  lcd.print(0, 0, "Exiting . . ");      // Print to APP LCD
  delay(100);
  Blynk.virtualWrite(V10, HIGH);        // Dock Button ON
  

}


void Clear_APP() {
  Blynk.virtualWrite(V0, LOW);   // Start Mowing Buton OFF
  Blynk.virtualWrite(V1, LOW);  // Go-Home Button OFF
  Blynk.virtualWrite(V2, LOW);  // Stop Button OFF
  Blynk.virtualWrite(V3, 0);    // Reset Voltage
  Blynk.virtualWrite(V5, 0);    // Loops
  Blynk.virtualWrite(V7, 0);    // Mow LED
  Blynk.virtualWrite(V8, 0);    // Dock LED Off
  Blynk.virtualWrite(V9, 0);    // TrackingLED OFF
  Blynk.virtualWrite(V10, LOW); // Dock Button OFF
  Blynk.virtualWrite(V11, 0);   // Compass LED OFF  
  Blynk.virtualWrite(V12, 0);   // Charging LED OFF  
}
