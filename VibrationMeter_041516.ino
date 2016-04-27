// Vibration/Shake Meter
// Keith Nason
// V 1.0.8
// 1/14/2016
//================-Changelog-================
/*

2/5/16 -- Changed pins for setup into box

2/12/16 -- Adjust Sampling

3/4/16 --  Set Amplitude in g's

3/6/16 -- Update amplitude calc, set analog ref 

3/11/16 -- Calibration adjustments

4/8/16 -- SD Logging fixes
          Clean up code, remove unused Zaxis code for space
          
4/15/16 -- Adjust output values for SD logging to make data more useful          
            Setup Amp display on time domain grapg
*/
//===========-Additional Comments-==============
/*
  -Could use more clean up
  -Reduce redundant code (e.g. different function for every axis reduced to single function and pass which function)
  -Better solution for logging and graphing simultaneously (might require changes to or additional hw) 

  -Code works well enough at this point and isn't too large, so it likely wont get reworked unless I have extra time to code/test
*/
//===========================================



// Define for FHT/FFT before loading lib
#define SCALE 1
#define LIN_OUT 1         // Turn on output function, Lin, Log, Oct, etc. FHT ouput must match, i.e. Lin, Log, Oct, etc.
//#define LOG_OUT 1
//#define FHT_N 256       // Set to FHT points, can be 2^5(16) -> 2^9(256) in multiples of 2^*
#define FHT_N 256         //Amount of sample data calculated from N

#define WINDOW 1
#define REORDER 1
#define OCT_NORM 1


//   Libs
#include <FHT.h>
#include <LCD5110_Graph.h>
#include <SPI.h>
#include <SD.h>


//SD Files
#define Xlog  "Xlog.csv" 
#define Ylog  "Ylog.csv" 
#define AccLog "AccLog.csv"

// Pins for acc axis
#define Xaxis A0       
#define Yaxis A1


// LCD for X axis
#define SCEy    40
#define RESETy  38
#define DCy     36
#define SDINy   34
#define SCLKy   32

// LCD for Y axis
#define SCEx    30
#define RESETx  28
#define DCx     26
#define SDINx   24
#define SCLKx   22


//Startup Options
#define SD_ON_pin         43
#define FHT_ON_pin        41
#define SD_ONLY_pin       39
#define DEBUG_pin         45
#define VerboseDebug_pin  47
#define Xaxis_ON_pin      49
#define Yaxis_ON_pin      51
#define CAL_PIN           53

// SD pins
#define SD_ChipSelect     10
#define SD_SPI_MOSI       11
#define SD_SPI_MISO       12
#define SD_SPI_SCK        13



// Setup LCDs, LCD5110(int SCK, int MOSI, int DC, int RST, int CS)
LCD5110 lcdx(SCLKx,SDINx,DCx,RESETx,SCEx);
LCD5110 lcdy(SCLKy,SDINy,DCy,RESETy,SCEy);


// Font for SD
extern uint8_t SmallFont[];     // For LCD print

//Set Variables                  0 = disable, 1 = enable
int TimeDisp = 0;
int FreqDisp = 0;
int DEBUG = 0;                   // Options 0 - off , 1 - Simple, 2 - verbose
int SD_ON = 0 ;
int FHT_ON = 1;
int Xaxis_enable = 1;
int Yaxis_enable = 1;
int cal = 0;



int PeakFreq, PeakAmp;          // Peak Amplitude and Frequency
int zero;                       // Used to Calibrate acc to ~zero
int binSize = 1;                // Freq bw per bin, used to get freq from bin #
int AmpG = 0 ;                  // Used to calculate g's from amplitude
int AnG = 72 / 10;              //Amplitude per g

int screen_delay = 0;           // Delay screen updates for readability if needed
int update_delay = 4;          // Add some time between sampling
int update_delaysd = 0 ;
int start_delay = 1000;
int sdlog_delay = 2;
int xzero = 0;
int yzero = 0;


int rectime[256];
int rectimeX[256];
int rectimeY[256]; 


double TotalTime;
double TotalTimefq;
String dataString;

int inputY[256];
int inputX[256];

int ycal = 500;
int xcal = 500;

int timeTaken = 0 ;

int advance = 4;

/////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

analogReference(EXTERNAL); // Set Analog Ref to 3.3v from AREF pin  

pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);

DebugSwitch();

  if (DEBUG >= 1){
  Serial.begin(57600);
  Serial.println("");
  Serial.println("Setup...");
  }
 
  
StartMsg();

if (SD_ON >= 1){
  InitSD();

  // Setup SD files, write titles to ready for data

  
  if (Xaxis_enable == 1){
    
  dataString = "----,----";
  writeSD_Xlog(dataString);

  dataString = "Time(ms),X (1/100g)";
  writeSD_Xlog(dataString);
    
  }

  if (Yaxis_enable == 1){
    
  dataString = "----,----";
  writeSD_Ylog(dataString);

  dataString = "Time(ms),Y (1/100g)";
  writeSD_Ylog(dataString);
    
  }
}}
/////////////////////////////////////////////////////////////////////////
void loop() {

if (DEBUG >= 1){
  Serial.println("Started Loop");
  TotalTime = millis();
  }
  
  // Calibrate Accel grab average current value
  calibrate(Yaxis);
  yzero = zero;
   
  calibrate(Xaxis);
  xzero = zero;
  
  // Use predefined calibration if selected
  if (cal == 1){
    xzero = xcal;
  }
  
  if (cal == 1) {
    yzero = ycal;
  }

if (DEBUG >= 1){
  if (cal == 1){
  Serial.println("Using Predefined Cal Data");
  }}
  CalMsg();

 for (int c=0 ; c < 1 ;){
  
// Data aquisition mode, only SD logging
if (SD_ON == 2){
  sdOnlyLogging();
}

else if (FHT_ON == 1){

 // Frequency Domain 
  for (int c=0 ; c < 1 ;)
{

  if (Xaxis_enable == 1){
  GetDataX(Xaxis,xzero);
  
  timeTaken= millis();
  
  sdlogX();
  
  if (DEBUG >= 1){
  int timesd = millis() - timeTaken;
  Serial.println(" Time taken to write SD");
  Serial.println(timesd);
  }
  
  fht_steps();
  lcdxOutFft();              // Output to LCD for X 
  
}

  if (Yaxis_enable == 1){
 GetDataY(Yaxis,yzero);
 
 timeTaken = millis();
 
 sdlogY();
 
 if (DEBUG >= 1){
  int timesd = millis() - timeTaken;
  Serial.println(" Time taken to write SD");
  Serial.println(timesd);
  }
 fht_steps();
 lcdyOutFft();             // Output to LCD for Y
  
}
}
}
else{

// Time Domain  
for (int c=0 ; c < 1 ;)
{
  
GetAxisData();
sdlogX();
sdlogY();
}} }}
/////////////////////////////////////////////////////////////////////////
void calc_PeakAmp_PeakFreq() {
  
// Calculate Peak Amplitude and Frequency

PeakFreq=0;
PeakAmp=0;

  for (int i=0; i < FHT_N/2;i++){ 
    if(fht_lin_out[i] > PeakAmp) {
      PeakAmp = fht_lin_out[i];
      PeakFreq = i*binSize;
      i++;
    }
  }
  AmpG = PeakAmp/AnG;
}

void calc_peakAmp() {
  PeakAmp=0;
  for (int i=0; i < FHT_N/2;i++){ 
    if(fht_input[i] > PeakAmp) {
      PeakAmp = fht_input[i];
      i++;
    }
  }
  AmpG = PeakAmp/AnG ;
}
////////////////////////////////////////////////////////////////////////////
void GetDataX(char axis, int zeroed){

// Grab acc data and place into array for input

if (DEBUG >= 1){
  Serial.println("Gathering X axis data");
}

  int i;
  int data;
  
  
  for(i=0;i<FHT_N;i++) {
    
   inputX[i] = analogRead(axis) - zeroed;
    fht_input[i] = inputX[i];
    rectimeX[i] = millis();
    
   
    if (DEBUG == 2){                            // Show the data position, raw value, calibration and calibrated data
  Serial.println("");
  Serial.println(i);
  Serial.println(fht_input[i] + zeroed);
  Serial.println(zeroed);
  Serial.println(fht_input[i]);
  
}
    delay(update_delay); 
  }}
///////////////////////////////////////////////////////////////////////
  void GetDataY(char axis, int zeroed){

// Grab acc data and place into array for input


if (DEBUG >= 1){
  Serial.println("Gathering Y axis data");
}

  int i;
  int data;
  
  
  for(i=0;i<FHT_N;i++) {
    
    inputY[i] = analogRead(axis) - zeroed;
    fht_input[i] = inputY[i];
    rectimeY[i] = millis();

  if (DEBUG == 2){
  Serial.println("");
  Serial.println(i);
  
  Serial.println(fht_input[i] + zeroed);
  Serial.println(zeroed);
  Serial.println(fht_input[i]);
  
}
    delay(update_delay); 
  }}
///////////////////////////////////////////////////////////////
void calibrate(char axis){
  
  int total = 0;
  
if (DEBUG >= 1){
   Serial.println("---Cal Axis--");
   Serial.println(String(axis));
}  

  for(int t=0;t<10;t++){
    
    if (DEBUG == 2){
    Serial.println(analogRead(axis));
    }
    
    total = (total + analogRead(axis));
  }
  
  zero = (total/10) ;
}
/////////////////////////////////////////////////////////////// 
void fht_steps(){
if (DEBUG >= 1){
  Serial.println("Performing FHT");
}
  
  fht_window();              // window the data for better frequency response, data = fht_input[]
  fht_reorder();             // reorder the data before doing the fht, 
  fht_run();                 // process the data in the fht, 
  //fht_mag_log();           // take the output of the fht magnitude, fht_input -> fht_output_xxxx[], xxxx being the format of the output i.e. Lin, Log, Oct, etc.  Must be enabled at start of code
  fht_mag_lin();
  
}
//////////////////////////////////////////////////////////////
void GetAxisData()
{
if (DEBUG >= 1){
  Serial.println("Grabbing accel data and graphing");
}


if (Yaxis_enable == 1){
GetDataY(Yaxis,yzero);
lcdyOutAcc();
}

if (Xaxis_enable == 1){
GetDataX(Xaxis,xzero);
lcdxOutAcc();
}}

