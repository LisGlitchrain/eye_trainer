#ifndef EYE_TRAINER_DISPLAYHELPER
#define EYE_TRAINER_DISPLAYHELPER 0

#include <TM1637Display.h>
#include "Defines.h"
#include "Settings.h"
#include "Enums.h"
#include "DisplayDefines.h"

class DisplayHelper
{
  // The amount of time (in milliseconds) between tests
  #define TEST_DELAY 250

public:
  DisplayHelper() { }

  void setup()
  {
    display.setBrightness(0x0f);
    m_DrawTitle = true;
  }

  void runTest()
  {
    int k;
    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
    display.setBrightness(0x0f);

    // All segments on
    display.setSegments(data);
    delay(TEST_DELAY);

    // Selectively set different digits
    data[0] = display.encodeDigit(0);
    data[1] = display.encodeDigit(1);
    data[2] = display.encodeDigit(2);
    data[3] = display.encodeDigit(3);
    display.setSegments(data);
    delay(TEST_DELAY);

    /*
    for(k = 3; k >= 0; k--) {
    display.setSegments(data, 1, k);
    delay(TEST_DELAY);
    }
    */

    display.clear();
    display.setSegments(data+2, 2, 2);
    delay(TEST_DELAY);

    display.clear();
    display.setSegments(data+2, 2, 1);
    delay(TEST_DELAY);

    display.clear();
    display.setSegments(data+1, 3, 1);
    delay(TEST_DELAY);


    // Show decimal numbers with/without leading zeros
    display.showNumberDec(0, false); // Expect: ___0
    delay(TEST_DELAY);
    display.showNumberDec(0, true);  // Expect: 0000
    delay(TEST_DELAY);
    display.showNumberDec(1, false); // Expect: ___1
    delay(TEST_DELAY);
    display.showNumberDec(1, true);  // Expect: 0001
    delay(TEST_DELAY);
    display.showNumberDec(301, false); // Expect: _301
    delay(TEST_DELAY);
    display.showNumberDec(301, true); // Expect: 0301
    delay(TEST_DELAY);
    display.clear();
    display.showNumberDec(14, false, 2, 1); // Expect: _14_
    delay(TEST_DELAY);
    display.clear();
    display.showNumberDec(4, true, 2, 2);  // Expect: __04
    delay(TEST_DELAY);
    display.showNumberDec(-1, false);  // Expect: __-1
    delay(TEST_DELAY);
    display.showNumberDec(-12);        // Expect: _-12
    delay(TEST_DELAY);
    display.showNumberDec(-999);       // Expect: -999
    delay(TEST_DELAY);
    display.clear();
    display.showNumberDec(-5, false, 3, 0); // Expect: _-5_
    delay(TEST_DELAY);
    display.showNumberHexEx(0xf1af);        // Expect: f1Af
    delay(TEST_DELAY);
    display.showNumberHexEx(0x2c);          // Expect: __2C
    delay(TEST_DELAY);
    display.showNumberHexEx(0xd1, 0, true); // Expect: 00d1
    delay(TEST_DELAY);
    display.clear();
    display.showNumberHexEx(0xd1, 0, true, 2); // Expect: d1__
    delay(TEST_DELAY);
    
    // Run through all the dots
    for(k=0; k <= 4; k++) {
      display.showNumberDecEx(0, (0x80 >> k), true);
      delay(TEST_DELAY);
    }

    // Brightness Test
    for(k = 0; k < 4; k++)
    data[k] = 0xff;
    for(k = 0; k < 7; k++) {
      display.setBrightness(k);
      display.setSegments(data);
      delay(TEST_DELAY);
    }
    
    // On/Off test
    for(k = 0; k < 4; k++) 
    {
      display.setBrightness(7, false);  // Turn off
      display.setSegments(data);
      delay(TEST_DELAY);
      display.setBrightness(7, true); // Turn on
      display.setSegments(data);
      delay(TEST_DELAY);  
    }
  
    // Done!
    display.setSegments(WORD_DONE);
  }

  void UpdateModeDisplay(bool _RunnerActive, DeviceMode _DeviceMode)
  {
    switch(_DeviceMode)
    {
      case DeviceMode::RUN:                   DrawRunInfo(_RunnerActive);   break;
      case DeviceMode::SETTINGS_MODE:         DrawSettingsRunModeInfo();    break;
      case DeviceMode::SETTINGS_BRIGHTNESS:   DrawSettingsBrightnessInfo(); break;
      case DeviceMode::SETTINGS_TIME_SWITCH:  DrawSettingsTimeSwitchInfo(); break;
      case DeviceMode::SETTINGS_TIME_MODE:    DrawSettingsTimeModeInfo();   break;
      case DeviceMode::TEST:                  DrawTestInfo();               break;
    }  
  }

  void DrawRunInfo(bool _Run)
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_RUN);
    }
    else if(_Run)
    {  
      display.setSegments(WORD(P, L, A, Y));
    }
    else
    {
      display.setSegments(WORD(P, A, U, S));
    }
  }

  void DrawSettingsRunModeInfo()
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_MODE);
    }
    else
    {  
      switch(Settings::getInstance().RunModeState)
      {
        case RunMode::FORWARD:  display.setSegments(WORD(F, W, R, D   )); break;
        case RunMode::BACKWARD: display.setSegments(WORD(B, A, C, K   )); break;
        case RunMode::BOTH:     display.setSegments(WORD(B, O, T, H   )); break;
        case RunMode::RANDOM:   display.setSegments(WORD(R, N, D, NONE)); break;
      }
    }
  }
    
  void DrawSettingsTimeSwitchInfo()
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_TIME_SWITCH);
    }
    else
    {
      display.showNumberDec(Settings::getInstance().getDisplaySwitchTime(), false);
    }
  }
      
  void DrawSettingsTimeModeInfo()
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_TIME_MODE);
    }
    else
    {  
      switch(Settings::getInstance().TimeModeState)
      {
        case TimeMode::CONST:       display.setSegments(WORD(C, N, S, T )); break;
        case TimeMode::MANUAL:      display.setSegments(WORD(M, A, N, L )); break;
        case TimeMode::DECREASING:  display.setSegments(WORD(D, E, C, R )); break;
      }
    }
  }
    
  void DrawSettingsBrightnessInfo()
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_BRIGHTNESS);
    }
    else
    {
      display.showNumberDec(Settings::getInstance().Brightness, false);
    }
  }
    
  void DrawTestInfo()
  {
    display.setSegments(WORD_TEST);
  }

  void setDrawTitle(bool _Value)
  {
    m_DrawTitle = _Value;
  }

  void getDrawTitle()
  {
    return m_DrawTitle;
  }

private:
  TM1637Display display = TM1637Display::TM1637Display(PIN_DISPLAY_CLK, PIN_DISPLAY_DIO);
  int currentTestNum = 0;
  bool m_DrawTitle = true;
};

#endif