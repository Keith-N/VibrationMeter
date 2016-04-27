

void DebugSwitch(){
  
pinMode(DEBUG_pin, INPUT_PULLUP);               // Setup debug
if (digitalRead(DEBUG_pin) == LOW){ 
  DEBUG = 1 ; 
}


pinMode(SD_ON_pin, INPUT_PULLUP);                // Turn on SD
if (digitalRead(SD_ON_pin) == LOW){ 
  SD_ON = 1 ; 
}


pinMode(FHT_ON_pin, INPUT_PULLUP);              // Set FHT or Time
if (digitalRead(FHT_ON_pin) == LOW){ 
  FHT_ON = 0 ; 
}

pinMode(VerboseDebug_pin, INPUT_PULLUP)  ;      // Set verbose debugging
if (digitalRead(VerboseDebug_pin) == LOW){ 
  DEBUG = 2 ; 
}

pinMode(SD_ONLY_pin, INPUT_PULLUP);             // Set Acc SD logging Only
if (digitalRead(SD_ONLY_pin) == LOW){ 
  SD_ON = 2 ; 
}


pinMode(Xaxis_ON_pin, INPUT_PULLUP);               // X axis Toggle
if (digitalRead(Xaxis_ON_pin) == LOW){ 
  Xaxis_enable = 0; 
}

pinMode(Yaxis_ON_pin, INPUT_PULLUP);               // Y axis Toggle
if (digitalRead(Yaxis_ON_pin) == LOW){ 
  Yaxis_enable = 0; 
}

pinMode(CAL_PIN, INPUT_PULLUP);
if (digitalRead(CAL_PIN) == LOW){
  cal = 1;
}

}
