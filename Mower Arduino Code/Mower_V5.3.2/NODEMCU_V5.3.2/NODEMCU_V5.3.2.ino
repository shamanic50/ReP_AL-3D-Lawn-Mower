

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeMCU(D2,D3);   //RXD2 TXD3

//#define LED LED_BUILTIN

#define LED D4      // on various NODEMCU boards the LED Pin is different.....

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WLAN";
char pass[] = "123456789910111213";

int buttonState = 0;
char  Version[16];
float BatteryVoltage;
bool Mower_Already_Started = 0;
bool Going_Home_Already = 0;
int i;
int j;
int k;
int transmit_blynk_code = 0;
float val_VoltNow;
int MowerMotionStatus;
int Error;
int loopstatus = 0;
int Docked;
int All;
int Mower_Stopped;
int RX_Data_Recieved;
int lastConnectionAttempt = millis();
int connectionDelay = 5000; // try to reconnect every 5 seconds

BlynkTimer timer;
WidgetLCD lcd(V6);


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void myTimerEvent()  {
  if (  (BatteryVoltage > 10) && (BatteryVoltage < 15) ){
      Blynk.virtualWrite(V3, BatteryVoltage);
  }


}

void setup()
{
  Serial.begin(9600);
  NodeMCU.begin(9600);
  Serial.println();
  Serial.println("Setting up NODEMCU........");
  Serial.println("");
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  digitalWrite(LED, HIGH);                          // Turn off LED Light
  WIFI_Connect();                                   // Connect to the WIFI
  Clear_APP();
  lcd.clear();
  pinMode(LED, OUTPUT);


}



//Functions
//***********************************


void WIFI_Connect() {
  
  int mytimeout = millis() / 1000;
  Serial.println();
  Serial.println("*********************************************");
  Blynk.begin(auth, ssid, pass);
  
  
  while (Blynk.connected() != WL_CONNECTED) {
    delay(500);
      if((millis() / 1000) > mytimeout + 3){                      // try for less than 4 seconds to connect to WiFi router
      break;
    }
  }
  
  if(!Blynk.connected()) {
    digitalWrite(LED, HIGH);
    Serial.println("NODEMCU Disconnected");
    Serial.println("Reconnecting . . . . . . ");
    WIFI_Connect();

    }
  else {
    digitalWrite(LED, LOW);
    Serial.println("Connected. . . . . .");
    // Setup a function to be called every second
    timer.setInterval(1000L, myTimerEvent);
    }
  }







void loop()  {

  loopstatus = loopstatus + 1 ;
  RX_Data_Recieved = 0;                         // resets the data received bool 
  
  if(!Blynk.connected()) {
    Blynk.run();
    timer.run();  
    digitalWrite(LED, HIGH);
    Serial.println("------------------------");
    Serial.println("NODEMCU Disconnected");
    Serial.println("Reconnecting ... ");
    WIFI_Connect() ;
    }
  else {
    Blynk.run();
    timer.run();  
    digitalWrite(LED, LOW);         //LED is inverted on a MODEMCU...
    Receive_All_From_MEGA();
    Update_Blynk_App_With_Status();
    Serial.println("------------------------");    
  }


}
