

String MaxHz = "max" ;
String Xcal ="";
String Ycal ="";
int i, k, l, x1=14, x2=x1+63, y1=9, y2=39;
// x1 x1,x2 x2 y1 y1, y2 y2

/////////////////////////////////////////////////////////////////////////////////////////

void lcdxOutFft(){
  
int i, n, Min, Max, Scale, ScaleMax;

  calc_PeakAmp_PeakFreq();
  lcdx.print("Hz",15,0);                                      // Peak Freq
  lcdx.printNumI(PeakFreq,LEFT,0);
  lcdx.print("*1/10g",RIGHT,0);                                     // Peak Amplitude
  lcdx.printNumI(AmpG, 35,0);
  //lcdy.print("Y",68,0);
  lcdx.drawLine(x1,y2,x2,y2);                                // Bottom Line
  lcdx.print("", x1-3, 41);                                  // Bottom Caption
  lcdx.print("Xaxis Freq", CENTER, 41);
  
  lcdx.print("", RIGHT, 41);
  dotLineVert(x1,y1,y2);                                    // Vert Left Line
  dotLineVert(x2,y1,y2);                                    // Vert Right Line
  
  
  
  
  Scale = (y2-y1)/5;                                        // Pixel/5
  
  if(PeakAmp < 130){ScaleMax= 150; Max = 15;}
  if(PeakAmp < 80){ ScaleMax=100; Min=40; Max = 10; }               // Set scale for max value
  if(PeakAmp < 40) { ScaleMax=50; Min=20; Max = 5;}
  if(PeakAmp < 20) { ScaleMax=30; Min=10;  Max = 3;}
  if(PeakAmp < 10) { ScaleMax=10; Min=4; Max = 1;}
  
  i=y2-(5*Scale);
  dotLineHor(x1,x2,i);                               // point line horizontal
  i=y2-(4*Scale);
  lcdx.printNumI(Max, 0, 15);                            // Left Mark
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(3*Scale);
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(2*Scale);
 // lcdx.printNumI(Min, 0, i-3);                              // Left Mark
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(1*Scale);
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  l=0;
  n=0;
  for(i=x1; i <= x2; i++) {
    k=fht_lin_out[n]*5*Scale/ScaleMax;
    lcdx.drawLine(i,y2-l,i+1,y2-k);
    l=k;
    n++;
  }
  lcdx.update();
  lcdx.clrScr();
}


void lcdyOutFft() {
  
int i, n, Min, Max, Scale, ScaleMax;
  calc_PeakAmp_PeakFreq();
  lcdy.print("Hz",15,0);                                      // Peak Freq
  lcdy.printNumI(PeakFreq,LEFT,0);
  lcdy.print(" *1/10g",RIGHT,0);                                     // Peak Amplitude
  lcdy.printNumI(AmpG, 35,0);
  //lcdy.print("Y",68,0);
  lcdy.drawLine(x1,y2,x2,y2);                                // Bottom Line
  lcdy.print("", x1-3, 41);                                  // Bottom Caption
  lcdy.print("Yaxis Freq", CENTER, 41);
  
  lcdy.print("", RIGHT, 41);
  ydotLineVert(x1,y1,y2);                                    // Vert Left Line
  ydotLineVert(x2,y1,y2);                                    // Vert Right Line
  
  Scale = (y2-y1)/5;            
  // Pixel/5
  if(PeakAmp < 130){ScaleMax= 150; Max = 15;}
  if(PeakAmp < 80){ ScaleMax=100; Min=40; Max = 10; }               // Set scale for max value
  if(PeakAmp < 40) { ScaleMax=50; Min=20; Max = 5;}
  if(PeakAmp < 20) { ScaleMax=30; Min=10;  Max = 3;}
  if(PeakAmp < 10) { ScaleMax=10; Min=4; Max = 1;}

  
  i=y2-(5*Scale);
  
  ydotLineHor(x1,x2,i);                               // point line horizontal
  i=y2-(4*Scale);
 lcdy.printNumI(Max, 0, i-3);                            // Left Mark
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(3*Scale);
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(2*Scale);
// lcdy.printNumI(Min, 0, i-3);                              // Left Mark
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(1*Scale);
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  l=0;
  n=0;
  for(i=x1; i <= x2; i++) {
    k=fht_lin_out[n]*5*Scale/ScaleMax;
    lcdy.drawLine(i,y2-l,i+1,y2-k);
    l=k;
    n++;
  }
  lcdy.update();
  lcdy.clrScr();
}

/////////////////////////////////////////////////////////////////////////////////////////
void dotLineHor(int x1, int x2, int y) {
                                                        // Dotted Horz Line
int m, n=0;
  for(m=x1; m < x2; m++) {
    if((n%3) == 0) lcdx.setPixel(m,y);
    n++;
  }
}  
 
void dotLineVert(int x, int y1, int y2) {
                                                        // Dotted Vert Line
int m, n=0;
  for(m=y1; m < y2; m++) {
    if((n%3) == 0) lcdx.setPixel(x,m);
    n++;
  }
}

////////////////////////////////////////////////////////////////////////////////////
void lcdyOutAcc() {
  
int i, n, Min, Scale, ScaleMax;
  calc_peakAmp();
  lcdy.print("Am",28,0);                                     // Peak Amplitude
  lcdy.printNumI(AmpG, 45,0);
  lcdy.print("Y",68,0);
  lcdy.drawLine(x1,y2,x2,y2);                                // Bottom Line
  lcdy.print("", x1-3, 41);                                 // Bottom Caption
  lcdy.print("ms", CENTER, 41);
  lcdy.print("", RIGHT, 41);
  ydotLineVert(x1,y1,y2);                                    // Vert Left Line
  ydotLineVert(x2,y1,y2);                                    // Vert Right Line
  
  Scale = (y2-y1)/5;                                        // Pixel/5
  
  
  if(PeakAmp < 100){ ScaleMax=120; Min=40; }               // Set scale for max value
  if(PeakAmp < 50) { ScaleMax=80; Min=20; }
  if(PeakAmp < 25) { ScaleMax=40; Min=10; }
  if(PeakAmp < 10) { ScaleMax=30; Min=4; }
  
  
  i=y2-(5*Scale);
  
  ydotLineHor(x1,x2,i);                               // point line horizontal
  i=y2-(4*Scale);
 // lcdy.printNumI(Min*2, 0, i-3);                            // Left Mark
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(3*Scale);
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(2*Scale);
 // lcdy.printNumI(Min, 0, i-3);                              // Left Mark
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(1*Scale);
  ydotLineHor(x1,x2,i);                               // Point Line horizontal
  l=0;
  n=0;
  
  // Draw Graph
  for(i=x1; i <= x2; i++) {
    k=(fht_input[n]/10 + ScaleMax/2)*5*Scale/ScaleMax;
    lcdy.drawLine(i,y2-l,i+1,y2-k);
    l=k;
    n++;
  }
  lcdy.update();
  delay(screen_delay);
  lcdy.clrScr();

}


void lcdxOutAcc() {
  
int i, n, Min, Scale, ScaleMax;
  calc_peakAmp();
  lcdx.print("Am",28,0);                                  // Peak Amplitude
  lcdx.printNumI(AmpG, 45,0);
  lcdx.print("X",68,0);
  lcdx.drawLine(x1,y2,x2,y2);                                // Bottom Line
  lcdx.print("", x1-3, 41);                                 // Bottom Caption
  lcdx.print("ms", CENTER, 41);
  lcdx.print("", RIGHT, 41);
  ydotLineVert(x1,y1,y2);                                    // Vert Left Line
  ydotLineVert(x2,y1,y2);                                    // Vert Right Line
  
  Scale = (y2-y1)/5;                                        // Pixel/5
  
  
  if(PeakAmp < 100){ ScaleMax=120; Min=40; }               // Set scale for max value
  if(PeakAmp < 50) { ScaleMax=80; Min=20; }
  if(PeakAmp < 25) { ScaleMax=40; Min=10; }
  if(PeakAmp < 10) { ScaleMax=30; Min=4; }
  
  
  i=y2-(5*Scale);
  
  ydotLineHor(x1,x2,i);                               // point line horizontal
  i=y2-(4*Scale);
  //lcdx.printNumI(Min*2, 0, i-3);                            // Left Mark
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(3*Scale);
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(2*Scale);
  //lcdx.printNumI(Min, 0, i-3);                              // Left Mark
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  i=y2-(1*Scale);
  dotLineHor(x1,x2,i);                               // Point Line horizontal
  l=0;
  n=0;
  // Draw Graph
  for(i=x1; i <= x2; i++) {
    k=(fht_input[n]/10 + ScaleMax/2)*5*Scale/ScaleMax ;
    lcdx.drawLine(i,y2-l,i+1,y2-k);
    l=k;
    n++;
  }
  lcdx.update();
  delay(screen_delay);
  lcdx.clrScr();

}


////////////////////////////////////////////////////////////////////////////////////
void ydotLineHor(int x1, int x2, int y) {
                                                        //Used for dotted Horz Line
int m, n=0;
  for(m=x1; m < x2; m++) {
    if((n%3) == 0) lcdy.setPixel(m,y);
    n++;
  }
}  
 
void ydotLineVert(int x, int y1, int y2) {
                                                        //Used for dotted Vert Line
int m, n=0;
  for(m=y1; m < y2; m++) {
    if((n%3) == 0) lcdy.setPixel(x,m);
    n++;
  }
}

/////////////////////////////////////////////////////////////////
void CalMsg(){

// Clear all LCDs

 // lcdz.InitLCD(60);
 // lcdz.clrScr();
  lcdy.InitLCD(60);
  lcdy.clrScr();
  lcdx.InitLCD(60);
  lcdx.setFont(SmallFont);
  lcdx.clrScr();
  

  if (Xaxis_enable == 1){
lcdx.InitLCD(60);
  lcdx.setFont(SmallFont);
  lcdx.clrScr();
  lcdx.print("Calibrated", CENTER, 0);
  lcdx.print("X axis", CENTER, 15);
 // lcdx.print(Xcal, CENTER, 30);
  lcdx.update();
  }

  if (Yaxis_enable == 1){
  lcdy.InitLCD(60);
  lcdy.setFont(SmallFont);
  lcdy.clrScr();
  lcdy.print("Calibrated", CENTER, 0);
  lcdy.print("Y axis", CENTER, 15);
 // lcdy.print(Ycal, CENTER, 30);
  lcdy.update();
  }

  
  delay(1500);
  
  
  clearScreens();
  
}


void StartMsg(){

  // Message displayed at start on the LCDs
  
  lcdy.InitLCD(60);
  lcdy.setFont(SmallFont);
  lcdy.clrScr();
  lcdy.print("Vibration", CENTER, 0);
  lcdy.print("Meter", CENTER, 15);
 lcdy.print("Keith N", CENTER, 30);
  lcdy.update();


  delay(start_delay);     // Allow enough time to see/read


  lcdy.InitLCD(60);
  lcdy.setFont(SmallFont);
  lcdy.clrScr();
  lcdy.print("Switches", CENTER, 0);
  lcdy.print("1 - SD Mode", LEFT, 8);
  lcdy.print("2 - Domain", LEFT, 16);
  lcdy.print("3 - SD+Graph", LEFT, 24);
  lcdy.print("4 - Debug", LEFT, 32);
  lcdy.print("5 - Debug+", LEFT, 40);
  lcdy.update();

  lcdx.InitLCD(60);
  lcdx.setFont(SmallFont);
  lcdx.clrScr();
  lcdx.print("6 - X axis", LEFT, 8);
  lcdx.print("7 - Y axis", LEFT, 16);
  lcdx.print("8 - Predef Cal", LEFT, 24);
  
  lcdx.update();
  
  delay(start_delay*2);     // Allow enough time to see/read

  lcdx.InitLCD(60);
  lcdx.setFont(SmallFont);
  lcdx.clrScr();
  lcdx.print("Initilizing", CENTER, 0);
  lcdx.print("Hardware", CENTER, 15);
  lcdx.print("", CENTER, 30);
  lcdx.update();

 lcdy.InitLCD(60);
  lcdy.setFont(SmallFont);
  lcdy.clrScr();

  // Display current settings
  
  if (SD_ON == 1) {
  lcdy.print("SD + Graph", LEFT, 0);
  }
  else if(SD_ON == 2){
   lcdy.print("SD Mode", LEFT, 0);

if (DEBUG == 1){
  lcdy.print("Debug ON", LEFT, 40);
  }
  else if (DEBUG == 2){
    lcdy.print("VerboseDebug", LEFT, 40);
  }
   
   lcdy.update();
  
  delay(start_delay);
   return;
  }
  else{
  lcdy.print("SD OFF", LEFT, 0);
  }
  if (DEBUG == 1){
  lcdy.print("Debug ON", LEFT, 40);
  }
  else if (DEBUG == 2){
    lcdy.print("VerboseDebug", LEFT, 40);
  }
  else{
  //lcdy.print("Debug OFF", LEFT, 15);  
  }
  if (FHT_ON == 1){
  lcdy.print(("Amp vs Freq"), LEFT, 10);
  }
  else{
    lcdy.print(("Amp vs Time"), LEFT, 10);
  }
  lcdy.update();

  if (Xaxis_enable == 1){
    lcdx.print(("Xaxis Enabled"),CENTER,0);
  }
  else {
    lcdx.print(("Xaxis Disabled"),CENTER,0);
  }

  if (Yaxis_enable == 1){
    lcdx.print(("Yaxis Enabled"),CENTER,15);
  }
  else {
    lcdx.print(("Yaxis Disabled"),CENTER,15);
  }


    lcdx.update();
    
  delay(start_delay);
  lcdx.clrScr();
  lcdy.clrScr();

  
}

void clearScreens(){
  lcdx.update();
  lcdx.clrScr();
  
  lcdy.update();
  lcdy.clrScr();
  
}
