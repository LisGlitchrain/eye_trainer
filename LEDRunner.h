#ifndef EYE_TRAINER_LEDRUNNER
#define EYE_TRAINER_LEDRUNNER 0

/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/
#include "Defines.h"
#include <ShiftRegister74HC595.h>
#include "Settings.h"
#include "WrapHelper.h"

class LEDRunner
{
public:
  LEDRunner() { }

  void setup()
  {
    pinMode(PIN_LED_GND_BUS, OUTPUT);
    pinMode(PIN_LED_SHIFT_REGISTER_DATA, OUTPUT);
    pinMode(PIN_LED_SHIFT_REGISTER_CLOCK, OUTPUT);
    pinMode(PIN_LED_SHIFT_REGISTER_LATCH, OUTPUT);
  }

  void manualUpdate(RunMode _RunMode, int _NextLEDIndexIncrement)
  {
    nextLED(_RunMode, _NextLEDIndexIncrement);
    m_LEDs.setAllLow();
    m_LEDs.set(m_CurrentLED, HIGH);
  }

  void update(unsigned long _DeltaTime)
  {
    if(!m_Run || Settings::getInstance().TimeModeState == TimeMode::MANUAL)
      return;

    m_CurrentTime += _DeltaTime;

    if(m_CurrentTime > Settings::getInstance().SwitchTime)
    {
      m_CurrentTime = 0;
      nextLED(Settings::getInstance().RunModeState, 1);
      m_LEDs.setAllLow();
      m_LEDs.set(m_CurrentLED, HIGH);
    }
  }

  void setRun(bool _Run)
  {
    m_Run = _Run;
  }

  void setBrightness(float _Brightness)
  {
    analogWrite(PIN_LED_GND_BUS, (MAX_BRIGHTNESS - _Brightness) / MAX_BRIGHTNESS * 255);
  }

  bool getRun()
  {
    return m_Run;
  }

  void runTest()
  {
    analogWrite(PIN_LED_GND_BUS, 120);

    for(int i = 0; i < 4; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(250);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(250);                       // wait for a second
    }

    m_LEDs.setAllHigh();
    delay(500); 
    m_LEDs.setAllLow();
    delay(500); 
    m_LEDs.setAllHigh();
    delay(500); 
    m_LEDs.setAllLow();
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
        m_LEDs.set(i, HIGH);
        delay(25); 
        m_LEDs.set(i, LOW); 
      }
      // setting single pins
      for (int i = MAX_LED_INDEX; i > 0; i--) 
      {
        m_LEDs.set(i, HIGH);
        delay(25); 
        m_LEDs.set(i, LOW); 
      }
    }

    m_LEDs.set(0, HIGH);
    delay(50); 
    
    for (int i = 0; i < MAX_LED_INDEX / 2; i++) 
    {
      m_LEDs.set(i, HIGH);
      m_LEDs.set(MAX_LED_INDEX - i, HIGH);
      delay(150); 
      m_LEDs.set(i, LOW);
      m_LEDs.set(MAX_LED_INDEX - i, LOW);
    }


    for(int j = 0; j < 5; j++)
    {
      for (int i = MAX_LED_INDEX / 2; i >= 0; i--) 
      {
        m_LEDs.set(i, HIGH);
        m_LEDs.set(MAX_LED_INDEX - i, HIGH); 
        delay(50); 
        m_LEDs.set(i, LOW);
        m_LEDs.set(MAX_LED_INDEX - i, LOW); 
      }
    }
    
    m_LEDs.setAllHigh(); // set all pins HIGH

    for(int i = 10; i > 0; i--)
    {
      analogWrite(PIN_LED_GND_BUS, i * 25.5);
      delay(100); 
    }

    delay(500);
  }

  void blink(const uint8_t _LedIndex, unsigned long _Time)
  {
    m_LEDs.setAllLow();
    m_LEDs.set(_LedIndex, HIGH);
    delay(_Time);
    m_LEDs.setAllLow();
  }

  void setAndClearOthers(const uint8_t _LedIndex, const uint8_t _Value)
  {
    m_LEDs.setAllLow();
    m_LEDs.set(_LedIndex, _Value);
  }

  void set(const uint8_t _LedIndex, const uint8_t _Value)
  {
    m_LEDs.set(_LedIndex, _Value);
  }

  void setAllHigh()
  {
    m_LEDs.setAllHigh();
  }

  void setAllLow()
  {
    m_LEDs.setAllLow();
  }

private:
  bool                                m_Run                   = false;
  unsigned long                       m_CurrentTime           = 0;
  int                                 m_CurrentLED            = 0;
  int                                 m_CurrentLEDPingPong    = 0;
  ShiftRegister74HC595<REGISTER_SIZE> m_LEDs                  = ShiftRegister74HC595<REGISTER_SIZE>::ShiftRegister74HC595(PIN_LED_SHIFT_REGISTER_DATA, PIN_LED_SHIFT_REGISTER_CLOCK, PIN_LED_SHIFT_REGISTER_LATCH);

  void nextLED(RunMode _RunMode, int _NextLEDIndexIncrement)
  {
    switch(_RunMode)
    {
      case RunMode::FORWARD: m_CurrentLED = wrapInt(m_CurrentLED + _NextLEDIndexIncrement, MAX_LED_INDEX + 1); break;
      case RunMode::BACKWARD: m_CurrentLED = wrapInt(m_CurrentLED - _NextLEDIndexIncrement, MAX_LED_INDEX + 1); break;
      case RunMode::BOTH:
        m_CurrentLEDPingPong  = wrapInt(m_CurrentLEDPingPong + _NextLEDIndexIncrement, (MAX_LED_INDEX + 1) * 2);
        m_CurrentLED = pingPong(m_CurrentLEDPingPong, MAX_LED_INDEX + 1); 
        break;
      case RunMode::RANDOM: m_CurrentLED = random(0, MAX_LED_INDEX + 1); break;
    }
  }
};

#endif