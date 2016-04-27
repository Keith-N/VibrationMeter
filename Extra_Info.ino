/*

By default Debugging, and SD will be off and the data will be graphed on the screen using FHT

Switch Settings
  The switch settings will be displayed on the Y LCD during start, default position is all down/off
  
  #1 Toggles SD logging                                     default is no SD
  #2 Toggles the domain of the graph to freq or time        default used frequency domain
  #3 Toggles SD logging ONLY                                default is off
  #4 Toggles Debugging                                      default is off
  #5 Toggles Verbose Debugging                              default is off
  #6 Toggles X axis 					    default is on
  #7 Toggles Y axis				            default is on
  #8 Toggles Z axis	(if available)			    default is off
  
When Debug is on (DEBUG = 1)
debugging will be enabled to announce the status to the serial terminal

When Debug+ or Verbose Debugging is on (DEBUG = 2)
collected and logged data will also be sent to the serial terminal

When SD is enabled the collected data will be written to the SD
The data will be limited due to the way data is collected and processed for the FHT and to the Graph

When SD Only Logging is on, graphing and FHT will be disabled
this will allow a more rapid and smooth collection of data to be sent to the SD card

To use debugging, you must connect a serial terminal set at 57600 baud to the proper COM port

To use any SD function, you must have an SD card formatted in FAT/FAT32 inserted

Switches 6, 7, and 8 toggle the specific axis as on/off 

===============================================================================================
Libraries/License/Code Examples

FHT - http://wiki.openmusiclabs.com/wiki/ArduinoFHT
License - GPL3

5110 LCD output - http://www.rinkydinkelectronics.com/library.php?id=48
License - Creative Commons Attribution-NonCommercial-ShareAlike 3.0- CC BY-NC-SA 3.0

Graphing to 5110, borrowed some code with modifications - http://shelvin.de/arduino-fft-auf-dem-5110-display-ausgeben/

SD - https://learn.adafruit.com/adafruit-data-logger-shield/for-the-mega-and-leonardo

License - GNU General Public License V3, some included libraries under GPL - GPL3


=========================================================================

Accelerometer Data

Output----------------------------------------------------

For SD logging

1g = approx 100, Output is in 1/100 g


Amplitude--------------------------------------------------

Output is ratiometric, when Vs = 2v   output is 195mv per g
                            Vs = 3.6v output is 360mv per g
So approx output is 100mv/g * Vs

When Vs is 3.3v output is 330mv per g
Using an AREF of 3.3v the analog read value is 1023 at 3.3v
or 310 per v

At 0g the output should be 1.65v,                1.65v*310/V = 613.8 for analog read value
At 1g the output would be 1.65v + .330v = 1.98v, 1.98v * 310/v = 716.1 for analog read value
Delta for 1g = 716.1 - 613.8 = 102.3

amplitude in g = analogval / 102.3

Bandwidth-------------------------------------------------

The bandwidth set using capacitors on accelerometer outputs.

using a 95nF (approximate value on acceleromerter) F(-3dB)= 5uF/95nF = 52.63 Hz
Data sheet shows 

50Hz   at   0.10  uF
100Hz  at   0.05  uF
200Hz  at   0.027 uF

Sample Rate----------------------------------------------

The sample rate is approximate and was calculated by recording the time per sample and sample set, with and without additional delay
to adjust rate.

Delay(ms)   Time(ms)    Rate(ms)      Freq(Hz)
            per Set     t/sample
            
0            31         121.09us       8258
5            1311       5.121          195
8            2079       8.121          123
10           2591       10.121         98


=====================================================================================
 
PIN INFO
--------------------
SD card
 
  Chip Select 10
  SPI MOSI    11
  SPI MISO    12
  SPI SCK     13
--------------------
LCD for  Y

  SCE        30
  RESET      28
  DC         26
  SDIN       24
  SCLK       22
--------------------
LCD for X

  SCE       40
  RESET     38
  DC        36
  SDIN      34
  SCLK      32
---------------------
LCD for Z

  SCE       41
  RESET     39
  DC        37
  SDIN      35
  SCLK      33
--------------------  
Analog Accel Axis

  X = A0
  Y = A1
  Z = A2
---------------------  
DIP Switch Settings
			Arduino	
  Name                    Pin      Switch
  SD Toggle                41        1
  Domain Toggle            43        2
  SD logging only          45        3
  Debug	          	       47        4
  Verbose Debug 	         49        5
  X axis toggle 	         51	       6	
  Y axis toggle		         53	       7
  Z axis toggle            55	       8
  
  
*/

