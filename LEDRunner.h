/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/
#include "Defines.h"
#include <ShiftRegister74HC595.h>

class LEDRunner
{
public:
  LEDRunner()
  {
  }

  LEDRunner(Settings _Settings)
  {
    m_Settings = _Settings;

  }

  void setup()
  {
    pinMode(PIN_LED_GND_BUS, OUTPUT);
    pinMode(PIN_LED_DATA, OUTPUT);
    pinMode(PIN_LED_CLOCK, OUTPUT);
    pinMode(PIN_LED_LATCH, OUTPUT);
  }

  void runTest()
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

  private:
    Settings m_Settings; 
    ShiftRegister74HC595<REGISTER_SIZE> sr = ShiftRegister74HC595<REGISTER_SIZE>::ShiftRegister74HC595(PIN_LED_DATA, PIN_LED_CLOCK, PIN_LED_LATCH);

};
