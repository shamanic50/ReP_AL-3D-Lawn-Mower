// All the Transmitted informtion functions


void Transmit_Blynk_Data_to_Mega() {
    i = transmit_blynk_code + 10;
  NodeMCU.print(i);
  NodeMCU.println("\p");
  delay(30);
  Serial.print("Blynk Code sent to MEGA: ");
  Serial.println(i);
  delay(20);
  Serial.println("------------------------------");
  }
