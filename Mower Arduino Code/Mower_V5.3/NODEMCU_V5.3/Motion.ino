

void Going_Home() {
  Serial.println("Going Home! -->");
  transmit_blynk_code = 2;
  Transmit_Blynk_Data_to_Mega();
  }

void Pause_Mower() {
  Serial.println("Mower Stopped/Paused -->");
  transmit_blynk_code = 1;
  Transmit_Blynk_Data_to_Mega();
  }



void StartMower() {
  Serial.println("Mower Started");
  transmit_blynk_code = 3;                    // Code used to let MEGA know what to do
  Transmit_Blynk_Data_to_Mega();              // Transmits that code to the MEGA
  }



void Exit_Dock() {
  Serial.println("Mower Stopped/Parked -->");
  transmit_blynk_code = 4;
  Transmit_Blynk_Data_to_Mega();
  }
