

/* Motor Functions
************************************************************************************/

void Motion_GoFullSpeed()     {
  if (Reverse_Steering == 0) {
      analogWrite(ENAPin, PWM_MaxSpeed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings                        
      analogWrite(ENBPin, PWM_MaxSpeed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
      }

  if (Reverse_Steering == 1) {
      analogWrite(ENBPin, PWM_MaxSpeed_RH);                             
      analogWrite(ENAPin, PWM_MaxSpeed_LH);
      }

  Serial.println("Go Full Speed ");
}

void Motion_GoFullSpeed_Out_Garage()     {
  //Speeds can be changed to give the mower a slight curve when exiting the Garage.
  analogWrite(ENAPin, 255);                                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin, 255);                                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
  Serial.println("Go Full Speed ");
}


void SetPins_ToGoForwards()     {                                 // Motor Bridge pins are set for both motors to move forwards.
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  Serial.println("Set Motor Forwards");
}


void SetPins_ToGoBackwards()      {                               // Motor Bridge pins are set for both motors to move Backwards
  digitalWrite(IN1Pin, HIGH);                                     // Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);                                     // Motor 2
  digitalWrite(IN4Pin, LOW);
  Serial.println("Set Motor Reverse");
  delay(20);
}


void Motion_StopMotors()  {                                     // Motor Bridge pins are set for both motors to stop
  digitalWrite(ENAPin, 0);
  digitalWrite(IN1Pin, LOW);                                    //Motor 1
  digitalWrite(IN2Pin, LOW);

  digitalWrite(ENBPin, 0);                                      //Motor 2
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);

  Serial.println("Motor Stop");
}


void SetPins_ToTurnLeft()       {                              // Pins are set so that Motors drive in opposite directions
  if (Reverse_Steering == 0) {
    digitalWrite(IN1Pin, LOW);                                   // Motor 1
    digitalWrite(IN2Pin, HIGH);
    digitalWrite(IN3Pin, HIGH);                                  // Motor 2
    digitalWrite(IN4Pin, LOW);
    }
 if (Reverse_Steering == 1) {
    digitalWrite(IN1Pin, HIGH);                                   // Motor 1
    digitalWrite(IN2Pin, LOW);
    digitalWrite(IN3Pin, LOW);                                    //Motor 2
    digitalWrite(IN4Pin, HIGH);
    }
 Serial.print("Turn Left");  
  }


void SetPins_ToTurnRight() {                                    // Pins are set so that Motors drive in opposite directions
    if (Reverse_Steering == 0) {
      digitalWrite(IN1Pin, HIGH);                                   // Motor 1
      digitalWrite(IN2Pin, LOW);
      digitalWrite(IN3Pin, LOW);                                    //Motor 2
      digitalWrite(IN4Pin, HIGH);
      }
   if (Reverse_Steering == 1) {
     digitalWrite(IN1Pin, LOW);                                   // Motor 1
     digitalWrite(IN2Pin, HIGH);
     digitalWrite(IN3Pin, HIGH);                                  // Motor 2
     digitalWrite(IN4Pin, LOW);
     }
  
  Serial.print("Turn Right");
}


// USed to turn the mower at a set speed.
void Motion_TurnSpeed() {

  if (Reverse_Steering == 0) {
      analogWrite(ENAPin, (PWM_MaxSpeed_RH - 0) );                                  // Change the 0 value to 10 or 20 to recuce the speed
      analogWrite(ENBPin, (PWM_MaxSpeed_LH - 0) );                                  // Change the 0 value to 10 or 20 to recuce the speed
      }

  if (Reverse_Steering == 1) {
      analogWrite(ENAPin, (PWM_MaxSpeed_LH - 0) );                                  // Change the 0 value to 10 or 20 to recuce the speed
      analogWrite(ENBPin, (PWM_MaxSpeed_RH - 0) );                                  // Change the 0 value to 10 or 20 to recuce the speed
      }
  

  Serial.print("Turn Speed RH : "); Serial.println(PWM_MaxSpeed_RH - 0);
  Serial.print("Turn Speed LH : "); Serial.println(PWM_MaxSpeed_LH - 0);
}

// Turns the mowing blades on
void SpinBlades()
{
  if (Blades_ON == 1) {                                       // Blades are turn ON in settings and will spin!
    delay(20);
    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);
    delay(20);
    analogWrite(RPWM, PWM_Blade_Speed);
    delay(20);
    Serial.println("Blade Motor Spinning.. Mind your fingers!");
  }                 

  if (Blades_ON == 0) {                                     // Blades are turn off in settings and will not spin!
    void StopSpinBlades();
    Serial.println("TEST MODE - BLADES STOPPED!");
  }
}

void StopSpinBlades()  {
  delay(20);
  digitalWrite(R_EN, LOW);
  digitalWrite(L_EN, LOW);
  delay(20);
  Serial.println("Blades Motor Stopped...!");
}


// Instructions to prepare the mower to start mowing.
void Prepare_To_Mow() {
  Serial.println("Preparing the mower to mow");
  Mower_Docked = 0;
  Docked_Button_Pressed = 0;
  lcd.clear();
  lcd.print("Prepare to Mow");
  delay(500);
  Mower_Docked = 0;
  delay(200);
  ADCMan.run();
  delay(200);
  Setup_Perimeter_Wire();                                                              // Recalibrates wire before mowing starts
  delay(500);
  SetPins_ToGoForwards();
  lcd.clear();                                                                         // Prints info to LCD display
  lcd.print("Start Mowing");
  Serial.println("Reseting Docking Switch and LED's");
  pinMode(LED_PIN, OUTPUT);
  delay(5);
  digitalWrite(LED_PIN, LOW);
  delay(5);
  lcd.clear();
  delay(500);
  Serial.println("Mower Prep completed....");
}

// Exit code to get clear of docking station - can be modified for other garage positions.
void Exit_From_Garage() {
    lcd.clear();
    lcd.print("Exiting Garage");
    delay(2000);
    SetPins_ToGoBackwards();                    // Prepare motors to go Backwards
    Motion_GoFullSpeed_Out_Garage();            // Move Backwards
    delay (7000);                               // Backwards time
    Motion_StopMotors;                          // Stop
    SetPins_ToTurnLeft();                       // Prepare motors to turn left
    Motion_TurnSpeed();                         // Turn
    delay(1000);                                 // Turn time
    Motion_StopMotors;                          // Stop
    SetPins_ToGoBackwards();                    // Set again to go backwards
    Motion_GoFullSpeed();                       // Move Backwards
    delay (500);                               // Backwards Time
    SetPins_ToTurnLeft();                       // Set to go left             
    Motion_TurnSpeed();                         // Turn
    delay(200);                                 // Turning time
    Motion_StopMotors();                          // Stop
    SetPins_ToGoForwards();                     // Set to go forwards
    Motion_StopMotors(); 
    lcd.clear();                                // Clears the LCD display
    lcd.print("Garage Clear");                  // Prints to the LCD screen
    Motion_StopMotors; 
    delay(500);
    lcd.clear();
}



//Exit Procedure for Mower into Garden area following the wire t a certain start point in the garden
void Exit_From_Docking_Station() {
  Serial.println("Exiting Docking Station");
  lcd.clear();                                                              // Specific insturctions to get the mower from the docking station
  lcd.print("Exit Docking to");                                             // into the garden at a good position to start Mowing
  lcd.setCursor(0, 1);
  lcd.print("Garden");                                               // Prints info to LCD display
  digitalWrite(Relay_Motors, LOW);
  lcd.clear();                    
  }

// Mower movements to position it in the garden once it finishes following the wire
void Move_Into_Garden_Zone_X()   {
    Serial.println("Exiting Wire at garden start position");      // With the same functions as above
    SetPins_ToTurnLeft();
    delay(200);
    Motion_TurnSpeed();                                             // Sets the speed of the turning motion
    delay(1500);
    Motion_StopMotors;
    delay(200);
    SetPins_ToGoForwards();
    Motion_GoFullSpeed();
    delay(1500);
    Motion_StopMotors();
    delay(500);
    Serial.println("At Garden Start Position");                     // With the same functions as above
    lcd.clear();
    lcd.print("Arrived");
    lcd.setCursor(0, 1);
    if (Exit_Zone == 1) lcd.print("Zone 1");  
    if (Exit_Zone == 2) lcd.print("Zone 2");                                            // Prints info to LCD display
    delay(2000);
    }

/*Steers the Mower depending on the PID input from the Algorythm*/
void Motion_Dynamic_PWM_Steering() {
  delay(7);
  if (Compass_Heading_Locked == 1) {
      Serial.print(" ");
      Serial.print(": PWM_R= ");
      Serial.print(PWM_Right);
      Serial.print(" : PWM_L= "); 
      Serial.print(PWM_Left);
      }
  
  if (Reverse_Steering == 0) {
      analogWrite(ENAPin, PWM_Right);                             // ENA low = Right Swerve   ENB low = Left Swerve
      analogWrite(ENBPin, PWM_Left);
      }

  if (Reverse_Steering == 1) {
      analogWrite(ENBPin, PWM_Right);                             // ENA low = Right Swerve   ENB low = Left Swerve
      analogWrite(ENAPin, PWM_Left);
      }

}

void Manuel_Start_Mower_Exit_Zone1() {
       Exit_From_Docking_Station();                        // Set up the mower to exit the docking station 
       delay(500);
       Exit_From_Garage();                                 // Back the mower out of the Garage and into position
       delay(500);
       FindWireTrack();      
       delay(300);      
       Track_Wire_Itterations = Track_Wire_Zone_1_Cycles;
       Exit_Zone = 1;
       Track_Wire_From_Dock_to_Zone_X();
       delay(500);
       Move_Into_Garden_Zone_X();
       delay(500);
       Prepare_To_Mow();
}


void Manuel_Start_Mower_Exit_Zone2() {

         Serial.println("Exit to Zone 2 - Free Mow");
         digitalWrite(Relay_Motors, LOW);
         delay(2000);
         Exit_From_Docking_Station();                       // Set up the mower to exit the docking station 
         delay(5);
         delay(500);
         Exit_From_Garage();                                // Move the Mower into position backing out of the docking station
         delay(500);  
         FindWireTrack();                                   // Located the boundary wire
         delay(300);      
         Track_Wire_Itterations = Track_Wire_Zone_2_Cycles; // Set the number of itterations of following the wire.
         Exit_Zone = 2;                                     // Zone called to exit at
         Track_Wire_From_Dock_to_Zone_X();                  // Runs the PID function and follows the wire until the itterations are completed
         delay(500);
         Move_Into_Garden_Zone_X();                         // Calls the motion function to move the mower off the wire into the garden
         delay(500);
         Prepare_To_Mow();                                  // Sets up the mower to go.
         delay(100);
         }



void Quick_Start() {
        lcd.clear();
        lcd.print("Quick Start");
        Serial.println("Mower Quick Start Selected");
        Menu_Mode_Selection = 0;
        delay(1000);
        lcd.clear();

}

// Motion Mower Status
void Calculate_Motion_Mower_Status() {

  if (MowerMotionStatus == 2)  {                       // Slow motion of Mower to detect objects
    Serial.println(" ");
    Serial.println("OFF WE GO!!!  Mowing the Lawn");
    Serial.println("*****************************");
    Serial.println(" ");
    delay(1);
    lcd.setCursor(0, 1);
    lcd.print("OFF WE GO!");
    SpinBlades();
    SetPins_ToGoForwards();
    Motion_GoFullSpeed();
    maxdistancesonar = 40;
    Serial.print("First Time Around - Ping set at: ");
    Serial.println(maxdistancesonar);
    delay(1);
  }

  if (MowerMotionStatus <= 5 && MowerMotionStatus > 2) {
    Serial.println("Being Careful for more Objects");
    SpinBlades();
    SetPins_ToGoForwards();
    Motion_GoFullSpeed();
    lcd.setCursor(0, 1);
    lcd.print("Mowing..        ");
    maxdistancesonar = 40;
    Serial.print("Up close ping - Ping set at: ");
    Serial.println(maxdistancesonar);
    delay(1);
  }

  if (MowerMotionStatus > 5) {
    SpinBlades();
    SetPins_ToGoForwards();
    if (Compass_Heading_Locked == 0) {
      Motion_GoFullSpeed();                      // Removes the full speed function if the mower is trying to hold to the compass heading.
      lcd.setCursor(0, 1);
      lcd.print("Mowing..        ");
    }
    if (Compass_Heading_Locked == 1) {            // if the Mower is tracking using the compass steer here
      Motion_Dynamic_PWM_Steering();              // Removes the full speed function if the mower is trying to hold to the compass heading.
      lcd.setCursor(0, 1);
      lcd.print("C-Mowing..     ");
      Serial.println("Compass PWM used...");
    }

    lcd.setCursor(13, 1);
    lcd.print(MowerMotionStatus);
    maxdistancesonar = 40;
    Serial.print("Looking way ahead at this speed - Ping set at: ");
    delay(1);
    Serial.println(maxdistancesonar);
    delay(1);


    /*This is a safety measure to turn the Mower incase it is stuck somewhere and no sensor has activated*/
    if (MowerMotionStatus > 150) {                    // 150 the max length for my garden. Adjust accordingly
      Serial.println("Better turn just incase..");
      StopSpinBlades();
      Serial.println("Reversing.....");
      Motion_StopMotors();
      delay(2000);
      lcd.setCursor(0, 8);
      lcd.print("Reversing");
      SetPins_ToGoBackwards();
      Motion_GoFullSpeed();
      delay(1800);
      lcd.print("Turn 90 -->      ");
      SetPins_ToTurnRight(); Serial.println("");                                                                         // Calls the motor funstion turn right
      delay(200);
      Motion_TurnSpeed();
      delay(3200);                                                                          // Time to Turn the Mower Right
      Motion_StopMotors();
      delay(50);
      SetPins_ToGoForwards();
      MowerMotionStatus = 3;
    }
  }
}
