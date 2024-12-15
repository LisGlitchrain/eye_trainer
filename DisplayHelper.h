#ifndef EYE_TRAINER_DISPLAYHELPER
#define EYE_TRAINER_DISPLAYHELPER 0

#include <TM1637Display.h>
#include "Defines.h"
#include "Settings.h"
#include "Enums.h"

class DisplayHelper
{
  // The amount of time (in milliseconds) between tests
  #define TEST_DELAY 250

public:
  DisplayHelper() { }
  
  DisplayHelper(Settings* _Settings) 
  {
    m_Settings = _Settings;
  }

  static const uint8_t NONE = 0;
  static const uint8_t A = SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G;
  static const uint8_t B = SEG_F | SEG_C | SEG_D | SEG_E | SEG_G;
  static const uint8_t C = SEG_A | SEG_F | SEG_E | SEG_D;
  static const uint8_t D = SEG_B | SEG_C | SEG_D | SEG_E | SEG_G;
  static const uint8_t E = SEG_A | SEG_D | SEG_E | SEG_F | SEG_G;
  static const uint8_t F = SEG_A | SEG_F | SEG_G | SEG_E;
  static const uint8_t G = SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
  static const uint8_t H = SEG_F | SEG_C | SEG_E | SEG_G;
  static const uint8_t I = SEG_B | SEG_C;
  static const uint8_t J = SEG_B | SEG_C | SEG_D;
  static const uint8_t K = SEG_A;
  static const uint8_t L = SEG_F | SEG_E | SEG_D;
  static const uint8_t M = SEG_C | SEG_G | SEG_E;
  static const uint8_t N = SEG_C | SEG_G | SEG_E;
  static const uint8_t O = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
  static const uint8_t P = SEG_A | SEG_B | SEG_G | SEG_F | SEG_E;
  static const uint8_t Q = SEG_G;
  static const uint8_t R = SEG_E | SEG_G;
  static const uint8_t S = SEG_A | SEG_F | SEG_G | SEG_C | SEG_D;
  static const uint8_t T = SEG_F | SEG_E | SEG_D | SEG_G;
  static const uint8_t U = SEG_C | SEG_D | SEG_E;
  static const uint8_t V = SEG_C | SEG_D | SEG_E | SEG_F | SEG_B;
  static const uint8_t W = SEG_D;
  static const uint8_t X = SEG_B | SEG_C | SEG_E | SEG_F | SEG_G;
  static const uint8_t Y = SEG_F | SEG_G | SEG_B | SEG_C;
  static const uint8_t Z = SEG_A | SEG_B | SEG_G | SEG_E | SEG_D;

  void setup()
  {
    display.setBrightness(0x0f);
    m_DrawTitle = true;
  }

  void buttonsTest()
  {
    bool btnMainState = digitalRead(PIN_BTN_MAIN);
    bool btnUpState = digitalRead(PIN_BTN_UP);
    bool btnDownState = digitalRead(PIN_BTN_DOWN);
    int numChanged = currentTestNum;

    if(btnMainState == HIGH)
    {
      numChanged = 0;
    }
    else if (btnUpState == HIGH)
    {
      numChanged++;
    }
    else if (btnDownState == HIGH)
    {
      numChanged--;
    }

    if(numChanged != currentTestNum)
    {
      currentTestNum = numChanged;
      display.clear();
      display.showNumberDec(currentTestNum, false);
    }
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

  void DrawRunInfo(bool _Run)
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_RUN);
    }
    else if(_Run)
    {  
      display.setSegments((const uint8_t[]) {P, L, A, Y});
    }
    else
    {
      display.setSegments((const uint8_t[]) {P, A, U, S});
    }
  }

  void DrawSettingsRunModeInfo(RunMode _RunMode)
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_MODE);
    }
    else
    {  
      switch(_RunMode)
      {
        case RunMode::FORWARD:  display.setSegments((const uint8_t[]) { F, W, R, D    }); break;
        case RunMode::BACKWARD: display.setSegments((const uint8_t[]) { B, A, C, K    }); break;
        case RunMode::BOTH:     display.setSegments((const uint8_t[]) { B, O, T, H    }); break;
        case RunMode::RANDOM:   display.setSegments((const uint8_t[]) { R, N, D, NONE }); break;
      }
    }
  }
    
  void DrawSettingsTimeSwitchInfo(int _SwitchTime)
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_TIME_SWITCH);
    }
    else
    {
      display.showNumberDec(_SwitchTime, false);
    }
  }
      
  void DrawSettingsTimeModeInfo(TimeMode _TimeMode)
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_TIME_MODE);
    }
    else
    {  
      switch(_TimeMode)
      {
        case TimeMode::CONST:       display.setSegments((const uint8_t[]) { C, N, S, T }); break;
        case TimeMode::MANUAL:      display.setSegments((const uint8_t[]) { M, A, N, L }); break;
        case TimeMode::DECREASING:  display.setSegments((const uint8_t[]) { D, E, C, R }); break;
      }
    }
  }
    
  void DrawSettingsBrightnessInfo(int _Brightness)
  {
    if(m_DrawTitle)
    {
      display.setSegments(WORD_BRIGHTNESS);
    }
    else
    {
      display.showNumberDec(_Brightness, false);
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
  Settings* m_Settings;
  int currentTestNum = 0;

  //seg A = upper ground
  //seg B = upper right
  //seg C = lower right

  uint8_t WORD_DONE[4]        = { D, O, N, E };
  uint8_t WORD_RUN[4]         = { R, U, N, NONE };
  uint8_t WORD_MODE[4]        = { R, M, O, D };
  uint8_t WORD_TIME_SWITCH[4] = { T, I, M, E };
  uint8_t WORD_TIME_MODE[4]   = { T, M, O, D };
  uint8_t WORD_BRIGHTNESS[4]  = { B, R, G, H };
  uint8_t WORD_TEST[4]        = { T, E, S, T };
  uint8_t WORD_[4]            = { SEG_G, SEG_G, SEG_G, SEG_G };

  bool m_DrawTitle = true;
};

#endif