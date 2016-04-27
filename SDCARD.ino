
void writeSD(String dataString)
{
  
  File dataFile = SD.open(AccLog, FILE_WRITE);
  // Check for data file, if exsists then write to it. If no SD then send error message
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();                            
  }
  else {
    dataFile.close();
    InitSD();
  }}


// For logging x/y
/////////////////////////////////////////////////////////////////////////
void writeSD_Xlog(String dataString)
{
  
  File dataFile = SD.open("Xlog.csv", FILE_WRITE);

  // Check for data file, if exsists then write to it. If no SD then send error message
  if (dataFile)  {
     dataFile.println(dataString);
    dataFile.close();
  }
  else {
    Serial.println("SD error!");
  }}
////////////////////////////////////////////////////////////////////
void writeSD_Ylog(String dataString)
{
  
  File dataFile = SD.open(Ylog, FILE_WRITE);

  // Check for data file, if exsists then write to it. If no SD then send error message
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();                                
  }
  
  else {
    dataFile.close();
    InitSD();
 }}

///////////////////////////////////////////////////////////////////////////

void sdError(){
  
  if (DEBUG == 1){
  Serial.println("SD Error");
  Serial.println("Make sure SD is inserted properly, and formatted in FAT32!");
  Serial.println("Insert SD or reset to continue");
  }
  
    lcdx.InitLCD(60);
    lcdx.setFont(SmallFont);
    lcdx.clrScr();
    lcdx.print("SD error!",CENTER,0);
    lcdx.print("insert to",CENTER,15);
    lcdx.print("continue",CENTER,30);
    lcdx.update();

    lcdy.InitLCD(60);
    lcdy.setFont(SmallFont);
    lcdy.clrScr();
    lcdy.print("SD must be",CENTER,0);
    lcdy.print("inserted",CENTER,10);
    lcdy.print("and formatted",CENTER,20);
    lcdy.print("in FAT32",CENTER,30);
    lcdy.update();

    delay(start_delay);
    
  if (DEBUG == 1){
    lcdx.InitLCD(60);
    lcdx.setFont(SmallFont);
    lcdx.clrScr();
    lcdx.print("Additional ",CENTER,0);
    lcdx.print("info in serial",CENTER,15);
    lcdx.print("terminal ...",CENTER,30);
    lcdx.update();
  }
  delay(start_delay);
}

///////////////////////////////////////////////////////////////////////////


void InitSD(){
if (DEBUG == 1){
  Serial.println("Initilizing SD");
}
  if (!SD.begin(10,11,12,13))      // Check For SD, if none is present send error message
  {
   sdError();
  InitSD();
  }
if (DEBUG == 1){  
Serial.println("Card initialized.");
}
 
}
/////////////////////////////////////////////////////////////////////////
void halt(){
  // Freeze up arduino 
  for (int i = 0; i > 5;i++)
  {
    delay(10000);
  }
}


////////////////////////////////////////////////////////////////////////

void sdOnlyLogging(){


 if (DEBUG == 1){
    Serial.println("Starting SD logging");
  }


    lcdx.InitLCD(60);
    lcdx.setFont(SmallFont);
    lcdx.clrScr();
    lcdx.print("SD Logging",CENTER,0);
    lcdx.print("Only",CENTER,15);
   // lcdx.print("No Graph",CENTER,30);
    lcdx.update();

    lcdy.InitLCD(60);
    lcdy.setFont(SmallFont);
    lcdy.clrScr();
   // lcdy.print("High-speed",CENTER,0);
    lcdy.print("Data",CENTER,0);
    lcdy.print("aquisition",CENTER,10);
    lcdy.print("to SD",CENTER,20);
    lcdy.update();

    dataString = "ms,X(1/100g),Y(1/100g)";
    writeSD(dataString);

   if (DEBUG == 2){
    Serial.println(dataString);
   }

 
 TotalTime = millis();
  while (SD_ON == 2){
    GrabDataSD();
    writeSD(dataString);
    delay(sdlog_delay);

    
    } } 

void GrabDataSD(){
   dataString="";                                                        // Clear data string

    dataString += millis() - TotalTime;
    dataString += ",";
                                                                          // Record XYZ Axis to string
   int sensor = (analogRead(Xaxis)-xzero);
    dataString += String(sensor);
    dataString += ",";
    sensor = (analogRead(Yaxis)-yzero);
    dataString += String(sensor); 
   // dataString += ",";
   // dataString += String(Zaxis);
    
    if (DEBUG == 2){
      Serial.println(dataString);
    }
}
//////////////////////////////////////////////////////////////
void sdlogY(){
   if (SD_ON == 1){
  
  if (DEBUG == 2 ){
             Serial.println("Logging Y to SD");
      }
      
      for(int c=0;c<FHT_N;) {
        
         dataString = "";
          dataString = String(rectimeY[c]);
          dataString += ",";
         dataString += String(inputY[c]);
          writeSD_Ylog(dataString);
          c=c+advance; // advance the sample to speed up sd write
             if (DEBUG == 2 ){
             Serial.println(dataString);
      }
          
   // delay(update_delaysd);
      
    }
  }
  
    if (DEBUG >= 1){
    if (SD_ON >= 1){
    Serial.println("Wrote to SD, Y axis data");
    }
  }
}

///////////////////////////////////////////////////////////

void sdlogX(){
   if (SD_ON == 1){
  
  if (DEBUG == 2 ){
             Serial.println("Logging X to SD");
      }
      
      for(int c=0;c<FHT_N;) {
        
         dataString = "";
          dataString = String(rectimeX[c]);
          dataString += ",";
         dataString += String(inputX[c]);
          writeSD_Xlog(dataString);
          c = c + advance;
             if (DEBUG == 2 ){
             Serial.println(dataString);
      }
          
   // delay(update_delaysd);
      
    }
  }
  
    if (DEBUG >= 1){
    if (SD_ON >= 1){
    Serial.println("Wrote to SD, X axis data");
    }
  }
  
}

