/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/
#include "Defines.h"
#include <ShiftRegister74HC595.h>
#include "Settings.h"

class LEDRunner
{
public:
  // LEDRunner()
  // {
  // }

  LEDRunner(Settings* _Settings)
  {
    this->m_Settings = _Settings;
  }

  void setup()
  {
    pinMode(PIN_LED_GND_BUS, OUTPUT);
    pinMode(PIN_LED_DATA, OUTPUT);
    pinMode(PIN_LED_CLOCK, OUTPUT);
    pinMode(PIN_LED_LATCH, OUTPUT);
  }

  void nextLED(RunMode _RunMode)
  {
    switch(_RunMode)
    {
      case RunMode::FORWARD: m_CurrentLED = wrapInt(m_CurrentLED + 1, MAX_LED_INDEX + 1); break;
      case RunMode::BACKWARD: m_CurrentLED = wrapInt(m_CurrentLED - 1, MAX_LED_INDEX + 1); break;
      //TODO: ADD PING PONG
      case RunMode::BOTH: m_CurrentLED = wrapInt(m_CurrentLED - 1, MAX_LED_INDEX + 1); break;
      case RunMode::RANDOM: m_CurrentLED = random(0, MAX_LED_INDEX + 1); break;
    }
  }

  void update(unsigned long _DeltaTime, int _SwitchTime, RunMode _RunMode, TimeMode _TimeMode)
  {
    if(!m_Run)
      return;

    m_CurrentTime += _DeltaTime;

    if(m_CurrentTime > _SwitchTime)
    {
      m_CurrentTime = 0;
      nextLED(_RunMode);
      sr.setAllLow();
      sr.set(m_CurrentLED, HIGH);
    }
  }

  void setRun(bool _Run)
  {
    m_Run = _Run;
  }

  void updateBrightness(float _Brightness)
  {
    analogWrite(PIN_LED_GND_BUS, (MAX_BRIGHTNESS - _Brightness) / MAX_BRIGHTNESS * 255);
  }

  bool getRun()
  {
    return m_Run;
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

  void blink(const uint8_t _LedIndex, unsigned long _Time)
  {
    sr.setAllLow();
    sr.set(_LedIndex, HIGH);
    delay(_Time);
    sr.setAllLow();
  }

  void setAndClearOthers(const uint8_t _LedIndex, const uint8_t _Value)
  {
    sr.setAllLow();
    sr.set(_LedIndex, _Value);
  }

  void set(const uint8_t _LedIndex, const uint8_t _Value)
  {
    sr.set(_LedIndex, _Value);
  }

  void setAllHigh()
  {
    sr.setAllHigh();
  }

  void setAllLow()
  {
    sr.setAllLow();
  }

  private:
    Settings* m_Settings; 
    bool m_Run = false;
    unsigned long m_CurrentTime = 0;
    int m_CurrentLED = 0;
    ShiftRegister74HC595<REGISTER_SIZE> sr = ShiftRegister74HC595<REGISTER_SIZE>::ShiftRegister74HC595(PIN_LED_DATA, PIN_LED_CLOCK, PIN_LED_LATCH);

  int wrapInt(int _Num,  int _Max)
  {
    if(_Num < 0)
    {
      return (_Max - _Num) % _Max;
    }
    if(_Num >= _Max)
    {
      return _Num % _Max;
    }

    return _Num;
  }

  int wrapInt(int _Num, int _Min, int _Max)
  {
    int num = _Num - _Min;
    int max = _Max - _Min;
    return wrapInt(num, max) + _Min;
  }
};
