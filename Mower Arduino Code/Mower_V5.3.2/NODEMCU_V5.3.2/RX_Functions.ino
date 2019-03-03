// All the recieved information functions


// Recieves a Package of Data from the MEGA about the Mowers Status
void Receive_All_From_MEGA()  {
        Serial.println("Reading All Codes");

        val_VoltNow = NodeMCU.parseFloat();
        if(NodeMCU.read()== '\z'){
        BatteryVoltage = val_VoltNow;
        Serial.print("Battery Voltage : ");
        Serial.println(BatteryVoltage);
        }
        
        Docked = NodeMCU.parseInt();
        if(NodeMCU.read()== '\a'){
        Serial.print("Docked : ");
        Serial.println(Docked);  
        }
        Error = NodeMCU.parseInt();
        if(NodeMCU.read()== '\b'){
        Serial.print("Error : ");
        Serial.println(Error);  
        }         
        MowerMotionStatus = NodeMCU.parseInt();
        if(NodeMCU.read()== '\c'){
        Serial.print("MowerMotionStatus : ");
        Serial.println(MowerMotionStatus);    
        RX_Data_Recieved = 1;        
        }
        Mower_Stopped = NodeMCU.parseInt();
        if(NodeMCU.read()== '\d'){
        Serial.print("Mower Stopped : ");
        Serial.println(Mower_Stopped);    
        RX_Data_Recieved = 1;   
        }
    
   }
