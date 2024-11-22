/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>
#include <TM1637Display.h>

#define PIN_LED_GND_BUS 6 
#define MAX_LED_INDEX 15
#define MAX_BRIGHTNESS 255.0
#define MIN_BRIGHTNESS 25.5

#define PIN_BTN_MAIN 9
#define PIN_BTN_UP 10
#define PIN_BTN_DOWN 11

#define PIN_DISPLAY_CLK 7
#define PIN_DISPLAY_DIO 8

#define BTN_DELAY

enum DeviceMode
{
  IDLE,
  SETTINGS_MODE,
  SETTINGS_BRIGHTNESS,
  SETTINGS_TIME,
  RUN
};

enum RunMode
{
  Forward,
  Backward,
  Bothward,
  Random,
};

enum TimeMode
{
  Const,
  Manual
};

//==============================================================
//state
//==============================================================

// create a global shift register object
// parameters: <number of shift registers> (data pin, clock pin, latch pin)
ShiftRegister74HC595<2> sr(5, 3, 4);

DeviceMode m_deviceMode;
RunMode m_RunMode;
TimeMode m_TimeMode;

float m_SwitchTime;
int m_CurrentLED;


//==============================================================
//end of state
//==============================================================

void setup() 
{ 
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_LED_GND_BUS, OUTPUT);
}

void loop()
{

  // // setting all pins at the same time to either HIGH or LOW
  // sr.setAllHigh(); // set all pins HIGH
  // delay(500);

  analogWrite(PIN_LED_GND_BUS, 120);

  for(int i = 0; i < 4; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(250);                       // wait for a second
  }

  sr.setAllHigh();
  delay(500); 
  sr.setAllLow();
  delay(500); 
  sr.setAllHigh();
  delay(500); 
  sr.setAllLow();
  delay(500); 

  for(int i = 0; i < 4; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(150);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(150);                       // wait for a second
  }

  for(int j = 0; j < 4; j++)
  {
    // setting single pins
    for (int i = 0; i < MAX_LED_INDEX; i++) 
    {
      sr.set(i, HIGH);
      delay(25); 
      sr.set(i, LOW); 
    }
        // setting single pins
    for (int i = MAX_LED_INDEX; i > 0; i--) 
    {
      sr.set(i, HIGH);
      delay(25); 
      sr.set(i, LOW); 
    }
  }

  sr.set(0, HIGH);
  delay(50); 
  
  for (int i = 0; i < MAX_LED_INDEX / 2; i++) 
  {
    sr.set(i, HIGH);
    sr.set(MAX_LED_INDEX - i, HIGH);
    delay(150); 
    sr.set(i, LOW);
    sr.set(MAX_LED_INDEX - i, LOW);
  }


  for(int j = 0; j < 5; j++)
  {
    for (int i = MAX_LED_INDEX / 2; i >= 0; i--) 
    {
      sr.set(i, HIGH);
      sr.set(MAX_LED_INDEX - i, HIGH); 
      delay(50); 
      sr.set(i, LOW);
      sr.set(MAX_LED_INDEX - i, LOW); 
    }
  }
  
  sr.setAllHigh(); // set all pins HIGH

  for(int i = 10; i > 0; i--)
  {
    analogWrite(PIN_LED_GND_BUS, i * 25.5);
    delay(100); 
  }

  delay(500);
  
}


//============================================================
//DISPLAY TEST!!!!!!!!!!!!!!!

// // The amount of time (in milliseconds) between tests
// #define TEST_DELAY   2000

// const uint8_t SEG_DONE[] = {
// 	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
// 	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
// 	SEG_C | SEG_E | SEG_G,                           // n
// 	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
// 	};

// TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);

// int currentNum = 0;

// void setup()
// {
//   pinMode(PIN_BTN_MAIN, INPUT);  
//   pinMode(PIN_BTN_UP, INPUT);  
//   pinMode(PIN_BTN_DOWN, INPUT);  
//   display.setBrightness(0x0f);
// }

// void loop()
// {
//   bool btnMainState = digitalRead(PIN_BTN_MAIN);
//   bool btnUpState = digitalRead(PIN_BTN_UP);
//   bool btnDownState = digitalRead(PIN_BTN_DOWN);
//   int numChanged = currentNum;

//   if(btnMainState == HIGH)
//   {
//     numChanged = 0;
//   }
//   else if (btnUpState == HIGH)
//   {
//     numChanged++;
//   }
//   else if (btnDownState == HIGH)
//   {
//     numChanged--;
//   }

//   if(numChanged != currentNum)
//   {
//     currentNum = numChanged;
//     display.clear();
//     display.showNumberDec(currentNum, false);
//   }

//   return;

//   int k;
//   uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
//   uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
//   display.setBrightness(0x0f);

//   // All segments on
//   display.setSegments(data);
//   delay(TEST_DELAY);

//   // Selectively set different digits
//   data[0] = display.encodeDigit(0);
//   data[1] = display.encodeDigit(1);
//   data[2] = display.encodeDigit(2);
//   data[3] = display.encodeDigit(3);
//   display.setSegments(data);
//   delay(TEST_DELAY);

//   /*
//   for(k = 3; k >= 0; k--) {
// 	display.setSegments(data, 1, k);
// 	delay(TEST_DELAY);
// 	}
//   */

//   display.clear();
//   display.setSegments(data+2, 2, 2);
//   delay(TEST_DELAY);

//   display.clear();
//   display.setSegments(data+2, 2, 1);
//   delay(TEST_DELAY);

//   display.clear();
//   display.setSegments(data+1, 3, 1);
//   delay(TEST_DELAY);


//   // Show decimal numbers with/without leading zeros
//   display.showNumberDec(0, false); // Expect: ___0
//   delay(TEST_DELAY);
//   display.showNumberDec(0, true);  // Expect: 0000
//   delay(TEST_DELAY);
// 	display.showNumberDec(1, false); // Expect: ___1
// 	delay(TEST_DELAY);
//   display.showNumberDec(1, true);  // Expect: 0001
//   delay(TEST_DELAY);
//   display.showNumberDec(301, false); // Expect: _301
//   delay(TEST_DELAY);
//   display.showNumberDec(301, true); // Expect: 0301
//   delay(TEST_DELAY);
//   display.clear();
//   display.showNumberDec(14, false, 2, 1); // Expect: _14_
//   delay(TEST_DELAY);
//   display.clear();
//   display.showNumberDec(4, true, 2, 2);  // Expect: __04
//   delay(TEST_DELAY);
//   display.showNumberDec(-1, false);  // Expect: __-1
//   delay(TEST_DELAY);
//   display.showNumberDec(-12);        // Expect: _-12
//   delay(TEST_DELAY);
//   display.showNumberDec(-999);       // Expect: -999
//   delay(TEST_DELAY);
//   display.clear();
//   display.showNumberDec(-5, false, 3, 0); // Expect: _-5_
//   delay(TEST_DELAY);
//   display.showNumberHexEx(0xf1af);        // Expect: f1Af
//   delay(TEST_DELAY);
//   display.showNumberHexEx(0x2c);          // Expect: __2C
//   delay(TEST_DELAY);
//   display.showNumberHexEx(0xd1, 0, true); // Expect: 00d1
//   delay(TEST_DELAY);
//   display.clear();
//   display.showNumberHexEx(0xd1, 0, true, 2); // Expect: d1__
//   delay(TEST_DELAY);
  
// 	// Run through all the dots
// 	for(k=0; k <= 4; k++) {
// 		display.showNumberDecEx(0, (0x80 >> k), true);
// 		delay(TEST_DELAY);
// 	}

//   // Brightness Test
//   for(k = 0; k < 4; k++)
// 	data[k] = 0xff;
//   for(k = 0; k < 7; k++) {
//     display.setBrightness(k);
//     display.setSegments(data);
//     delay(TEST_DELAY);
//   }
  
//   // On/Off test
//   for(k = 0; k < 4; k++) 
//   {
//     display.setBrightness(7, false);  // Turn off
//     display.setSegments(data);
//     delay(TEST_DELAY);
//     display.setBrightness(7, true); // Turn on
//     display.setSegments(data);
//     delay(TEST_DELAY);  
//   }
 
//   // Done!
//   display.setSegments(SEG_DONE);

//   while(1);
// }

