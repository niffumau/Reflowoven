
/*******************************************************************************
* Title: Reflow Oven Controller
* Version: 1.20
* Date: 26-11-2012
* Company: Rocket Scream Electronics
* Author: Lim Phang Moh
* Website: www.rocketscream.com
* 
* Brief
* =====
* This is an example firmware for our Arduino compatible reflow oven controller. 
* The reflow curve used in this firmware is meant for lead-free profile 
* (it's even easier for leaded process!). You'll need to use the MAX31855 
* library for Arduino if you are having a shield of v1.60 & above which can be 
* downloaded from our GitHub repository. Please check our wiki 
* (www.rocketscream.com/wiki) for more information on using this piece of code 
* together with the reflow oven controller shield. 
*
* Temperature (Degree Celcius)                 Magic Happens Here!
* 245-|                                               x  x  
*     |                                            x        x
*     |                                         x              x
*     |                                      x                    x
* 200-|                                   x                          x
*     |                              x    |                          |   x   
*     |                         x         |                          |       x
*     |                    x              |                          |
* 150-|               x                   |                          |
*     |             x |                   |                          |
*     |           x   |                   |                          | 
*     |         x     |                   |                          | 
*     |       x       |                   |                          | 
*     |     x         |                   |                          |
*     |   x           |                   |                          |
* 30 -| x             |                   |                          |
*     |<  60 - 90 s  >|<    90 - 120 s   >|<       90 - 120 s       >|
*     | Preheat Stage |   Soaking Stage   |       Reflow Stage       | Cool
*  0  |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
*                                                                Time (Seconds)
*
* This firmware owed very much on the works of other talented individuals as
* follows:/*******************************************************************************
  Title: Tiny Reflow Controller
  Version: 2.00
  Date: 03-03-2019
  Company: Rocket Scream Electronics
  Author: Lim Phang Moh
  Website: www.rocketscream.com

  Brief
  =====
  This is an example firmware for our Arduino compatible Tiny Reflow Controller.
  A big portion of the code is copied over from our Reflow Oven Controller
  Shield. We added both lead-free and leaded reflow profile support in this
  firmware which can be selected by pressing switch #2 (labelled as LF|PB on PCB)
  during system idle. The unit will remember the last selected reflow profile.
  You'll need to use the MAX31856 library for Arduino.

  Lead-Free Reflow Curve
  ======================

  Temperature (Degree Celcius)                 Magic Happens Here!
  245-|                                               x  x
      |                                            x        x
      |                                         x              x
      |                                      x                    x
  200-|                                   x                          x
      |                              x    |                          |   x
      |                         x         |                          |       x
      |                    x              |                          |
  150-|               x                   |                          |
      |             x |                   |                          |
      |           x   |                   |                          |
      |         x     |                   |                          |
      |       x       |                   |                          |
      |     x         |                   |                          |
      |   x           |                   |                          |
  30 -| x             |                   |                          |
      |<  60 - 90 s  >|<    90 - 120 s   >|<       90 - 120 s       >|
      | Preheat Stage |   Soaking Stage   |       Reflow Stage       | Cool
   0  |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ |_ _ _ _ _
                                                                 Time (Seconds)

  Leaded Reflow Curve (Kester EP256)
  ==================================

  Temperature (Degree Celcius)         Magic Happens Here!
  219-|                                       x  x
      |                                    x        x
      |                                 x              x
  180-|                              x                    x
      |                         x    |                    |   x
      |                    x         |                    |       x
  150-|               x              |                    |           x
      |             x |              |                    |
      |           x   |              |                    |
      |         x     |              |                    |
      |       x       |              |                    |
      |     x         |              |                    |
      |   x           |              |                    |
  30 -| x             |              |                    |
      |<  60 - 90 s  >|<  60 - 90 s >|<   60 - 90 s      >|
      | Preheat Stage | Soaking Stage|   Reflow Stage     | Cool
   0  |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ _ _ _ _ _ _
                                                                 Time (Seconds)

  This firmware owed very much on the works of other talented individuals as
  follows:
  ==========================================
  Brett Beauregard (www.brettbeauregard.com)
  ==========================================
  Author of Arduino PID library. On top of providing industry standard PID
  implementation, he gave a lot of help in making this reflow oven controller
  possible using his awesome library.

  ==========================================
  Limor Fried of Adafruit (www.adafruit.com)
  ==========================================
  Author of Arduino MAX31856 and SSD1306 libraries. Adafruit has been the source 
  of tonnes of tutorials, examples, and libraries for everyone to learn.

  ==========================================
  Spence Konde (www.drazzy.com/e/)
  ==========================================
  Maintainer of the ATtiny core for Arduino:
  https://github.com/SpenceKonde/ATTinyCore

  Disclaimer
  ==========
  Dealing with high voltage is a very dangerous act! Please make sure you know
  what you are dealing with and have proper knowledge before hand. Your use of
  any information or materials on this Tiny Reflow Controller is entirely at
  your own risk, for which we shall not be liable.

  Licences
  ========
  This Tiny Reflow Controller hardware and firmware are released under the
  Creative Commons Share Alike v3.0 license
  http://creativecommons.org/licenses/by-sa/3.0/
  You are free to take this piece of code, use it and modify it.
  All we ask is attribution including the supporting libraries used in this
  firmware.

  Required Libraries
  ==================
  - Arduino PID Library:
    >> https://github.com/br3ttb/Arduino-PID-Library
  - Adafruit MAX31856 Library:
    >> https://github.com/adafruit/Adafruit_MAX31856
  - Adafruit SSD1306 Library:
    >> https://github.com/adafruit/Adafruit_SSD1306
  - Adafruit GFX Library:
    >> https://github.com/adafruit/Adafruit-GFX-Library

  Revision  Description
  ========  ===========
  2.00      Support V2 of the Tiny Reflow Controller:
            - Based on ATMega328P 3.3V @ 8MHz
            - Uses SSD1306 128x64 OLED
  1.00      Initial public release:
            - Based on ATtiny1634R 3.3V @ 8MHz
            - Uses 8x2 alphanumeric LCD

*******************************************************************************/


#define VERSION 2             // Replace with 1 or 2 *-**********************************************************

// ***** INCLUDES *****
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>


#if VERSION == 1
#include <Adafruit_LiquidCrystal.h>   // updated 
#elif VERSION == 2
#include <Adafruit_GFX.h>      // Comment for VERSION 1
#include <Adafruit_SSD1306.h>  // Comment for VERSION 1 
#endif

//#include <Adafruit_MAX31856.h> 
#include <Adafruit_MAX31855.h> 
//#include <MAX31855.h> 
#include <PID_v1.h>

#include "main.h"


// ***** TYPE DEFINITIONS *****
typedef enum REFLOW_STATE
{
  REFLOW_STATE_IDLE,
  REFLOW_STATE_PREHEAT,
  REFLOW_STATE_SOAK,
  REFLOW_STATE_REFLOW,
  REFLOW_STATE_COOL,
  REFLOW_STATE_COMPLETE,
  REFLOW_STATE_TOO_HOT,
  REFLOW_STATE_ERROR
} reflowState_t;

typedef enum REFLOW_STATUS
{
  REFLOW_STATUS_OFF,
  REFLOW_STATUS_ON
} reflowStatus_t;

typedef	enum SWITCH
{
  SWITCH_NONE,
  SWITCH_1,
  SWITCH_2
} switch_t;

typedef enum DEBOUNCE_STATE
{
  DEBOUNCE_STATE_IDLE,
  DEBOUNCE_STATE_CHECK,
  DEBOUNCE_STATE_RELEASE
} debounceState_t;

typedef enum REFLOW_PROFILE
{
  REFLOW_PROFILE_LEADFREE,
  REFLOW_PROFILE_LEADED
} reflowProfile_t;

// ***** CONSTANTS *****
// ***** GENERAL *****




const char compile_date[] = __DATE__ " " __TIME__;


// ***** GENERAL PROFILE CONSTANTS *****
#define PROFILE_TYPE_ADDRESS 0
#define TEMPERATURE_ROOM 50
#define TEMPERATURE_SOAK_MIN 150
#define TEMPERATURE_COOL_MIN 100
#define SENSOR_SAMPLING_TIME 1000
#define SOAK_TEMPERATURE_STEP 5

// ***** LEAD FREE PROFILE CONSTANTS *****
#define TEMPERATURE_SOAK_MAX_LF 200
#define TEMPERATURE_REFLOW_MAX_LF 250
#define SOAK_MICRO_PERIOD_LF 9000

// ***** LEADED PROFILE CONSTANTS *****
#define TEMPERATURE_SOAK_MAX_PB 180
#define TEMPERATURE_REFLOW_MAX_PB 224
#define SOAK_MICRO_PERIOD_PB 10000

// ***** SWITCH SPECIFIC CONSTANTS *****
#define DEBOUNCE_PERIOD_MIN 100

// ***** DISPLAY SPECIFIC CONSTANTS *****
#define UPDATE_RATE 100

// ***** PID PARAMETERS *****
// ***** PRE-HEAT STAGE *****
#define PID_KP_PREHEAT 100
#define PID_KI_PREHEAT 0.025
#define PID_KD_PREHEAT 20
// ***** SOAKING STAGE *****
#define PID_KP_SOAK 300
#define PID_KI_SOAK 0.05
#define PID_KD_SOAK 250
// ***** REFLOW STAGE *****
#define PID_KP_REFLOW 300
#define PID_KI_REFLOW 0.05
#define PID_KD_REFLOW 350
#define PID_SAMPLE_TIME 1000

#if VERSION == 2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define X_AXIS_START 18 // X-axis starting position
#endif

// ***** LCD MESSAGES *****
const char* lcdMessagesReflowStatus[] = {
  "Ready",
  "Pre",
  "Soak",
  "Reflow",
  "Cool",
  "Done!",
  "Hot!",
  "Error"
};

// ***** DEGREE SYMBOL FOR LCD *****
unsigned char degree[8]  = {
  140, 146, 146, 140, 128, 128, 128, 128
};

// ***** PIN ASSIGNMENT *****
#if VERSION == 1
unsigned char ssrPin = 46;
unsigned char thermocoupleCSPin = 10;     //48
unsigned char lcdRsPin = 8;       //9
unsigned char lcdEPin = 9;      //9
unsigned char lcdD4Pin = 4;     //4
unsigned char lcdD5Pin = 5;       //5
unsigned char lcdD6Pin = 6;       // 6
unsigned char lcdD7Pin = 7;         // 7
unsigned char buzzerPin = 44;         // 44
unsigned char switchPin = A0;         // A0
//unsigned char ledPin = LED_BUILTIN;
unsigned char ledPin = 4;
#elif VERSION == 2
unsigned char ssrPin = A0;              //46
unsigned char ssrPinBottom = A1;
unsigned char fanPin = A2;               // A1

unsigned char thermocoupleCSPin = 4;     // 48, 10
unsigned char ledPin = 6;                   // 4
unsigned char buzzerPin = 9;               // 44
unsigned char switchStartStopPin = 3;       // 3
unsigned char switchLfPbPin = 5;            //2
#endif

// ***** PID CONTROL VARIABLES *****
double setpoint;
double input;
double output;
double kp = PID_KP_PREHEAT;
double ki = PID_KI_PREHEAT;
double kd = PID_KD_PREHEAT;
int windowSize;
unsigned long windowStartTime;
unsigned long nextCheck;
unsigned long nextRead;
unsigned long updateLcd;
unsigned long timerSoak;
unsigned long buzzerPeriod;
unsigned char soakTemperatureMax;
unsigned char reflowTemperatureMax;
unsigned long soakMicroPeriod;
// Reflow oven controller state machine state variable
reflowState_t reflowState;
// Reflow oven controller status
reflowStatus_t reflowStatus;
// Reflow profile type
reflowProfile_t reflowProfile;
// Switch debounce state machine state variable
debounceState_t debounceState;
// Switch debounce timer
long lastDebounceTime;
// Switch press status
switch_t switchStatus;
switch_t switchValue;
switch_t switchMask;
// Seconds timer
unsigned int timerSeconds;
// Thermocouple fault status
//unsigned char fault;
uint8_t fault;
#if VERSION == 2      // for some reason this was set to ifdef???
unsigned int timerUpdate;
unsigned char temperature[SCREEN_WIDTH - X_AXIS_START];
unsigned char x;
#endif

// PID control interface
PID reflowOvenPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
#if VERSION == 1
// LCD interface
Adafruit_LiquidCrystal lcd(lcdRsPin, lcdEPin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);    // added Adafruit_
#elif VERSION == 2
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
#endif

/*
 * Deal with the different stupid thermocopuple interfaces
 * 
 * Note that the cheap ali express version of the max31855 seems to be missing a few things
 * it is NOT 5 v tollerant, it might like max of 4 v.  Also needs a bypass capacitor on the thermocouple
 * I think they said 10 microfarad.
 * Shoudl really have a level shifter/logic converter
 */


#ifdef ADAFRUIT_MAX31856_H
Adafruit_MAX31856 thermocouple = Adafruit_MAX31856(thermocoupleCSPin);
#elif defined(ADAFRUIT_MAX31855_H) 
Adafruit_MAX31855 thermocouple = Adafruit_MAX31855(thermocoupleCSPin);
//Adafruit_MAX31855 thermocouple = Adafruit_MAX31855(hermocoupleCSPin, SPI1);   // not really sure
#endif





void MAX_Initialize(void){
  Serial.println("Initialize Thermocouple Interface...");  
  thermocouple.begin();   // Initialize thermocouple interface

#ifdef ADAFRUIT_MAX31855_H

#elif ADAFRUIT_MAX31856_H
  //delay(2);
  thermocouple.setThermocoupleType(MAX31856_TCTYPE_K);
  thermocouple.setColdJunctionFaultThreshholds(0, 500);
  thermocouple.setTempFaultThreshholds(0, 500);

  Serial.print("Thermocouple type: ");
  switch (thermocouple.getThermocoupleType() ) {
      case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
      case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
      case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
      case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
      case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
      case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
      case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
      case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
      case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
      case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
      default: Serial.println("Unknown"); break;
  }
#endif

}

double MAX_GetTemp(void) {
  double _tempreading, _tempreading_internal;
  uint8_t _fault;

#ifdef ADAFRUIT_MAX31855_H
  _tempreading_internal = thermocouple.readInternal();
  _tempreading = thermocouple.readCelsius();

  // Maybe just try and read a fault here?

  if (isnan(_tempreading)) {
    Serial.println("Thermocouple fault(s) detected!");
    uint8_t e = thermocouple.readError();
    if (e & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple is open - no connections.");
    if (e & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple is short-circuited to GND.");
    if (e & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple is short-circuited to VCC.");
  } else {
    //Serial.print("C:"); Serial.print(input);
    //Serial.print("\tInternal:");  Serial.println(_tempreading_internal);
  }

#elif defined(ADAFRUIT_MAX31856_H)
  _tempreading = thermocouple.readThermocoupleTemperature();
  _fault = thermocouple.readFault();     // Check for thermocouple fault

  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) Serial.println("Cold Junction Range Fault");
    if (fault & MAX31856_FAULT_TCRANGE) Serial.println("Thermocouple Range Fault");
    if (fault & MAX31856_FAULT_CJHIGH)  Serial.println("Cold Junction High Fault");
    if (fault & MAX31856_FAULT_CJLOW)   Serial.println("Cold Junction Low Fault");
    if (fault & MAX31856_FAULT_TCHIGH)  Serial.println("Thermocouple High Fault");
    if (fault & MAX31856_FAULT_TCLOW)   Serial.println("Thermocouple Low Fault");
    if (fault & MAX31856_FAULT_OVUV)    Serial.println("Over/Under Voltage Fault");
    if (fault & MAX31856_FAULT_OPEN)    Serial.println("Thermocouple Open Fault");
  }
    
#endif

  //Serial.print("Temp:");Serial.println(input); Serial.println(F(""));     // Debug Temperature
  return _tempreading;
}

/*
// check rotary encoder; set temperature, toggle boost mode, enter setup menu accordingly
uint16_t  SetTemp, ShowTemp, gap, Step;

// reads current rotary encoder value
int getRotary() {
  return (count >> ROTARY_TYPE);
}

void ROTARYCheck() {
  // set working temperature according to rotary encoder value
  SetTemp = getRotary();
  
  // check rotary encoder switch
  uint8_t c = digitalRead(BUTTON_PIN);
  if ( !c && c0 ) {
    beep();
    buttonmillis = millis();
    while( (!digitalRead(BUTTON_PIN)) && ((millis() - buttonmillis) < 500) );
    if ((millis() - buttonmillis) >= 500) SetupScreen();
    else {
      inBoostMode = !inBoostMode;
      if (inBoostMode) boostmillis = millis();
      handleMoved = true;
    }
  }
  c0 = c;

  // check timer when in boost mode
  if (inBoostMode && timeOfBoost) {
    goneSeconds = (millis() - boostmillis) / 1000;
    if (goneSeconds >= timeOfBoost) {
      inBoostMode = false;              // stop boost mode
      beep();                           // beep if boost mode is over
      beepIfWorky = true;               // beep again when working temperature is reached
    }
  }
}
*/

void tone_error(void) {
  for (int i=0; i < 10; i++) {
    tone(buzzerPin, 2000,50);
    delay(100);
  }
  digitalWrite(buzzerPin, LOW); 
}

void tone_beep(void) {
  tone(buzzerPin, 2000,50);
  delay(100);
  digitalWrite(buzzerPin, LOW); 
}

void tone_start(void) {
  tone(buzzerPin, 1000,200);
  delay(200);
  tone(buzzerPin, 2000,200);
  delay(200);
  tone(buzzerPin, 3000,200);
  delay(200);
  digitalWrite(buzzerPin, LOW); 
}
void tone_finish(void) {
  tone(buzzerPin, 3000,200);
  delay(200);
  tone(buzzerPin, 2000,200);
  delay(200);
  tone(buzzerPin, 2000,200);
  delay(200);
  digitalWrite(buzzerPin, LOW); 
}

void setup()
{
  Serial.begin(115200);           // Serial communication at 115200 bps
  Serial.println("Reflow Oven started");

  // Check current selected reflow profile
  unsigned char value = EEPROM.read(PROFILE_TYPE_ADDRESS);
  if ((value == 0) || (value == 1))
  {
    // Valid reflow profile value
    reflowProfile = value;
  }
  else
  {
    // Default to lead-free profile
    EEPROM.write(PROFILE_TYPE_ADDRESS, 0);
    reflowProfile = REFLOW_PROFILE_LEADFREE;
  }

  // SSR pin initialization to ensure reflow oven is off
  digitalWrite(ssrPin, LOW);
  pinMode(ssrPin, OUTPUT);
  digitalWrite(ssrPinBottom, LOW);
  pinMode(ssrPinBottom, OUTPUT);

  // Buzzer pin initialization to ensure annoying buzzer is off
  digitalWrite(buzzerPin, LOW);
  pinMode(buzzerPin, OUTPUT);

  // LED pins initialization and turn on upon start-up (active high)
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // setup pins
  pinMode(switchStartStopPin,INPUT_PULLUP);
  pinMode(switchLfPbPin,INPUT_PULLUP);


  // Start-up splash
  //digitalWrite(buzzerPin, HIGH);
#if VERSION == 1
  Serial.println("Initialize LCD...");
  lcd.begin(8, 2);
  lcd.createChar(0, degree);
  lcd.clear();
  lcd.print(F(" Tiny  "));
  lcd.setCursor(0, 1);
  lcd.print(F(" Reflow "));
#elif VERSION == 2
  Serial.println("Initialize OLED...");

 
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  //if(!oled.begin(0x3C)) {
    Serial.println(F("SSD1306 Allocation failed"));
    for(;;);  // loop forever
  }
  //oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.display();
#endif

  tone_start(); // why not
  //digitalWrite(buzzerPin, LOW); 
  
  delay(2000);    // Needed for the display, should show us a splash screen for the OLED

#if VERSION == 1
  lcd.clear();
  lcd.print(F(" v1.00  "));
  lcd.setCursor(0, 1);
  lcd.print(F("26-07-17"));
  delay(2000);
  lcd.clear();
#elif VERSION == 2
  Serial.println("Display Start Message on OLED...");
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println(F("     Tiny Reflow"));
  oled.println(F("     Controller"));
  oled.println();
  oled.println(F("       v2.00"));
  oled.println();
  oled.println(F("      04-03-19"));
  oled.display();
  delay(3000);
  Serial.println("Clear Display OLED...");
  oled.clearDisplay();
#endif


  // Turn off LED (active high)
  digitalWrite(ledPin, LOW);
  // Set window size
  windowSize = 2000;
  // Initialize time keeping variable
  nextCheck = millis();
  // Initialize thermocouple reading variable
  nextRead = millis();
  // Initialize LCD update timer
  updateLcd = millis();

  MAX_Initialize();

 
}

void loop()
{
  // Current time
  unsigned long now;

  // Time to read thermocouple?
  if (millis() > nextRead)
  {
    // Read thermocouple next sampling period
    nextRead += SENSOR_SAMPLING_TIME;
    


    input = MAX_GetTemp();  // Read current temperature

    if (isnan(input)) {

      reflowState = REFLOW_STATE_ERROR;
      reflowStatus = REFLOW_STATUS_OFF;
      Serial.println(F("Error"));

    } 


 
  }

  if (millis() > nextCheck)
  {
    // Check input in the next seconds
    nextCheck += SENSOR_SAMPLING_TIME;
    // If reflow process is on going
    if (reflowStatus == REFLOW_STATUS_ON)
    {
      // Toggle red LED as system heart beat
      digitalWrite(ledPin, !(digitalRead(ledPin)));
      // Increase seconds timer for reflow curve plot
      timerSeconds++;
      // Send temperature and time stamp to serial
      Serial.print(timerSeconds);
      Serial.print(F(","));
      Serial.print(setpoint);
      Serial.print(F(","));
      Serial.print(input);
      Serial.print(F(","));
      Serial.println(output);
    }
    else
    {
      // Turn off red LED
      digitalWrite(ledPin, LOW);
    }
  }

  if (millis() > updateLcd)
  {
    // Update LCD in the next 100 ms
    updateLcd += UPDATE_RATE;
#if VERSION == 1
    // Clear LCD
    lcd.clear();
    // Print current system state
    lcd.print(lcdMessagesReflowStatus[reflowState]);
    lcd.setCursor(6, 0);
    if (reflowProfile == REFLOW_PROFILE_LEADFREE)
    {
	    lcd.print(F("LF"));
    }
    else
    {
      lcd.print(F("PB"));
    }
    lcd.setCursor(0, 1);
    
    // If currently in error state
    if (reflowState == REFLOW_STATE_ERROR)
    {
      // Thermocouple error (open, shorted)
      lcd.print(F("TC Error"));
    }
    else
    {
      // Display current temperature
      lcd.print(input);
#if ARDUINO >= 100
      // Display degree Celsius symbol
      lcd.write((uint8_t)0);
#else
      // Display degree Celsius symbol
      lcd.print(0, BYTE);
#endif
      lcd.print("C ");
    }
#elif VERSION == 2
    oled.clearDisplay();
    oled.setTextSize(2);
    oled.setCursor(0, 0);
    oled.print(lcdMessagesReflowStatus[reflowState]);
    oled.setTextSize(1);
    oled.setCursor(115, 0);

    if (reflowProfile == REFLOW_PROFILE_LEADFREE)
    {
      oled.print(F("LF"));
    }
    else
    {
      oled.print(F("PB"));
    }
    
    // Temperature markers
    oled.setCursor(0, 18);
    oled.print(F("250"));
    oled.setCursor(0, 36);
    oled.print(F("150"));
    oled.setCursor(0, 54);
    oled.print(F("50"));
    // Draw temperature and time axis
    oled.drawLine(18, 18, 18, 63, WHITE);
    oled.drawLine(18, 63, 127, 63, WHITE);
    oled.setCursor(115, 0);

    // If currently in error state
    if (reflowState == REFLOW_STATE_ERROR)
    {
      oled.setCursor(80, 9);
      oled.print(F("TC Error"));
    }
    else
    {
      // Right align temperature reading
      if (input < 10) oled.setCursor(91, 9);
      else if (input < 100) oled.setCursor(85,9);
      else oled.setCursor(80, 9);
      // Display current temperature
      oled.print(input);
      oled.print((char)247);
      oled.print(F("C"));
    }
    
    if (reflowStatus == REFLOW_STATUS_ON)
    {
      // We are updating the display faster than sensor reading
      if (timerSeconds > timerUpdate)
      {
        // Store temperature reading every 3 s
        if ((timerSeconds % 3) == 0)
        {
          timerUpdate = timerSeconds;
          unsigned char averageReading = map(input, 0, 250, 63, 19);
          if (x < (SCREEN_WIDTH - X_AXIS_START))
          {
            temperature[x++] = averageReading;
          }
        }
      }
    }
    
    unsigned char timeAxis;
    for (timeAxis = 0; timeAxis < x; timeAxis++)
    {
      oled.drawPixel(timeAxis + X_AXIS_START, temperature[timeAxis], WHITE);
    }
    
    // Update screen
    oled.display();
#endif
  }

  // Reflow oven controller state machine
  switch (reflowState)
  {
    case REFLOW_STATE_IDLE:
      // If oven temperature is still above room temperature
      if (input >= TEMPERATURE_ROOM)
      {
        reflowState = REFLOW_STATE_TOO_HOT;
      }
      else
      {
        // If switch is pressed to start reflow process
        if (switchStatus == SWITCH_1)
        {
          // Send header for CSV file
          Serial.println(F("Time,Setpoint,Input,Output"));
          // Intialize seconds timer for serial debug information
          timerSeconds = 0;
          
          #if VERSION == 2
          // Initialize reflow plot update timer
          timerUpdate = 0;
          
          for (x = 0; x < (SCREEN_WIDTH - X_AXIS_START); x++)
          {
            temperature[x] = 0;
          }
          // Initialize index for average temperature array used for reflow plot
          x = 0;
          #endif
          
          // Initialize PID control window starting time
          windowStartTime = millis();
          // Ramp up to minimum soaking temperature
          setpoint = TEMPERATURE_SOAK_MIN;
          // Load profile specific constant
          if (reflowProfile == REFLOW_PROFILE_LEADFREE)
          {
            soakTemperatureMax = TEMPERATURE_SOAK_MAX_LF;
            reflowTemperatureMax = TEMPERATURE_REFLOW_MAX_LF;
            soakMicroPeriod = SOAK_MICRO_PERIOD_LF;
          }
          else
          {
            soakTemperatureMax = TEMPERATURE_SOAK_MAX_PB;
            reflowTemperatureMax = TEMPERATURE_REFLOW_MAX_PB;
            soakMicroPeriod = SOAK_MICRO_PERIOD_PB;
          }
          // Tell the PID to range between 0 and the full window size
          reflowOvenPID.SetOutputLimits(0, windowSize);
          reflowOvenPID.SetSampleTime(PID_SAMPLE_TIME);
          // Turn the PID on
          reflowOvenPID.SetMode(AUTOMATIC);
          // Proceed to preheat stage
          reflowState = REFLOW_STATE_PREHEAT;
        }
      }
      break;

    case REFLOW_STATE_PREHEAT:
      reflowStatus = REFLOW_STATUS_ON;
      // If minimum soak temperature is achieve
      if (input >= TEMPERATURE_SOAK_MIN)
      {
        // Chop soaking period into smaller sub-period
        timerSoak = millis() + soakMicroPeriod;
        // Set less agressive PID parameters for soaking ramp
        reflowOvenPID.SetTunings(PID_KP_SOAK, PID_KI_SOAK, PID_KD_SOAK);
        // Ramp up to first section of soaking temperature
        setpoint = TEMPERATURE_SOAK_MIN + SOAK_TEMPERATURE_STEP;
        // Proceed to soaking state
        reflowState = REFLOW_STATE_SOAK;
      }
      break;

    case REFLOW_STATE_SOAK:
      // If micro soak temperature is achieved
      if (millis() > timerSoak)
      {
        timerSoak = millis() + soakMicroPeriod;
        // Increment micro setpoint
        setpoint += SOAK_TEMPERATURE_STEP;
        if (setpoint > soakTemperatureMax)
        {
          // Set agressive PID parameters for reflow ramp
          reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
          // Ramp up to first section of soaking temperature
          setpoint = reflowTemperatureMax;
          // Proceed to reflowing state
          reflowState = REFLOW_STATE_REFLOW;
        }
      }
      break;

    case REFLOW_STATE_REFLOW:
      // We need to avoid hovering at peak temperature for too long
      // Crude method that works like a charm and safe for the components
      if (input >= (reflowTemperatureMax - 5))
      {
        // Set PID parameters for cooling ramp
        reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
        // Ramp down to minimum cooling temperature
        setpoint = TEMPERATURE_COOL_MIN;
        // Proceed to cooling state
        reflowState = REFLOW_STATE_COOL;
      }
      break;

    case REFLOW_STATE_COOL:
      // If minimum cool temperature is achieve
      if (input <= TEMPERATURE_COOL_MIN)
      {
        // Retrieve current time for buzzer usage
        buzzerPeriod = millis() + 1000;
        // Turn on buzzer to indicate completion
        //digitalWrite(buzzerPin, HIGH);
        tone_finish();


        // Turn off reflow process
        reflowStatus = REFLOW_STATUS_OFF;
        // Proceed to reflow Completion state
        reflowState = REFLOW_STATE_COMPLETE;
      }
      break;

    case REFLOW_STATE_COMPLETE:
      if (millis() > buzzerPeriod)
      {
        // Turn off buzzer
        //digitalWrite(buzzerPin, LOW);
        tone_finish();
        // Reflow process ended
        reflowState = REFLOW_STATE_IDLE;
      }
      break;

    case REFLOW_STATE_TOO_HOT:
      // If oven temperature drops below room temperature
      if (input < TEMPERATURE_ROOM)
      {
        // Ready to reflow
        reflowState = REFLOW_STATE_IDLE;
      }
      break;

    case REFLOW_STATE_ERROR:
      // Check for thermocouple fault

      /*
      fault = thermocouple.readFault();

      // If thermocouple problem is still present
      if ((fault & MAX31856_FAULT_CJRANGE) ||
          (fault & MAX31856_FAULT_TCRANGE) ||
          (fault & MAX31856_FAULT_CJHIGH) ||
          (fault & MAX31856_FAULT_CJLOW) ||
          (fault & MAX31856_FAULT_TCHIGH) ||
          (fault & MAX31856_FAULT_TCLOW) ||
          (fault & MAX31856_FAULT_OVUV) ||
          (fault & MAX31856_FAULT_OPEN))
      {
        // Wait until thermocouple wire is connected
        reflowState = REFLOW_STATE_ERROR;
      }*/
  
      if (isnan(input)) {
        reflowState = REFLOW_STATE_ERROR;
      }
      else
      {
        // Clear to perform reflow process
        reflowState = REFLOW_STATE_IDLE;
      }
      break;
  }

  // If switch 1 is pressed
  if (switchStatus == SWITCH_1)
  {
    // If currently reflow process is on going
    if (reflowStatus == REFLOW_STATUS_ON)
    {
      // Button press is for cancelling
      // Turn off reflow process
      reflowStatus = REFLOW_STATUS_OFF;
      // Reinitialize state machine
      reflowState = REFLOW_STATE_IDLE;
    }
  }
  // Switch 2 is pressed
  else if (switchStatus == SWITCH_2)
  {
    // Only can switch reflow profile during idle
    if (reflowState == REFLOW_STATE_IDLE)
    {
      // Currently using lead-free reflow profile
      if (reflowProfile == REFLOW_PROFILE_LEADFREE)
      {
        // Switch to leaded reflow profile
        reflowProfile = REFLOW_PROFILE_LEADED;
        EEPROM.write(PROFILE_TYPE_ADDRESS, 1);
      }
      // Currently using leaded reflow profile
      else
      {
        // Switch to lead-free profile
        reflowProfile = REFLOW_PROFILE_LEADFREE;
        EEPROM.write(PROFILE_TYPE_ADDRESS, 0);
      }
    }
  }
  // Switch status has been read
  switchStatus = SWITCH_NONE;

  // Simple switch debounce state machine (analog switch)
  switch (debounceState)
  {
    case DEBOUNCE_STATE_IDLE:
      // No valid switch press
      switchStatus = SWITCH_NONE;

      switchValue = readSwitch();

      // If either switch is pressed
      if (switchValue != SWITCH_NONE)
      {
        // Keep track of the pressed switch
        switchMask = switchValue;
        // Intialize debounce counter
        lastDebounceTime = millis();
        // Proceed to check validity of button press
        debounceState = DEBOUNCE_STATE_CHECK;
      }
      break;

    case DEBOUNCE_STATE_CHECK:
      switchValue = readSwitch();
      if (switchValue == switchMask)
      {
        // If minimum debounce period is completed
        if ((millis() - lastDebounceTime) > DEBOUNCE_PERIOD_MIN)
        {
          // Valid switch press
          switchStatus = switchMask;
          // Proceed to wait for button release
          debounceState = DEBOUNCE_STATE_RELEASE;
        }
      }
      // False trigger
      else
      {
        // Reinitialize button debounce state machine
        debounceState = DEBOUNCE_STATE_IDLE;
      }
      break;

    case DEBOUNCE_STATE_RELEASE:
      switchValue = readSwitch();
      if (switchValue == SWITCH_NONE)
      {
        // Reinitialize button debounce state machine
        debounceState = DEBOUNCE_STATE_IDLE;
      }
      break;
  }

  // PID computation and SSR control
  if (reflowStatus == REFLOW_STATUS_ON)
  {
    now = millis();

    reflowOvenPID.Compute();

    if ((now - windowStartTime) > windowSize)
    {
      // Time to shift the Relay Window
      windowStartTime += windowSize;
    }
    if (output > (now - windowStartTime)) { 
      digitalWrite(ssrPin, HIGH);
      digitalWrite(ssrPinBottom, HIGH);
      }
    else {
      digitalWrite(ssrPin, LOW);
      digitalWrite(ssrPinBottom, LOW);
    }
  }
  // Reflow oven process is off, ensure oven is off
  else
  {
    digitalWrite(ssrPin, LOW);
    digitalWrite(ssrPinBottom, LOW);
  }
}

switch_t readSwitch(void)
{
  int switchAdcValue = 0;
#if VERSION == 1
  // Analog multiplexing switch
  switchAdcValue = analogRead(switchPin);

  // Add some allowance (+10 ADC step) as ADC reading might be off a little
  // due to 3V3 deviation and also resistor value tolerance
  if (switchAdcValue >= 1000) return SWITCH_NONE;
  if (switchAdcValue <= 10) return SWITCH_1;
  if (switchAdcValue <= 522) return SWITCH_2;

#elif VERSION == 2
  // Switch connected directly to individual separate pins
  if (digitalRead(switchStartStopPin) == LOW) return SWITCH_1;
  if (digitalRead(switchLfPbPin) == LOW) return SWITCH_2;

#endif

  return SWITCH_NONE;
}
