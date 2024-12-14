#include "Defines.h"
#include "DisplayHelper.h"
#include "Settings.h"
#include "LEDRunner.h"
#include "InputHelper.h"
#include "Enums.h"

class EyeTrainerMain
{
public:
  //==============================================================
  //state
  //==============================================================

  enum DeviceMode m_deviceMode = DeviceMode::RUN;

  Settings m_Settings = Settings();
  LEDRunner m_LEDRunner = LEDRunner(&m_Settings);
  DisplayHelper m_DisplayHelper = DisplayHelper(&m_Settings);
  InputHelper m_InputHelper = InputHelper();
  bool m_DrawTitle = true;
  unsigned long m_PrevTime = 0;

  //==============================================================
  //end of state
  //==============================================================

  EyeTrainerMain() { }

  void setup() 
  { 
      pinMode(LED_BUILTIN, OUTPUT);
      m_LEDRunner.setup();
      m_DisplayHelper.setup();
      m_InputHelper.setup();
      UpdateModeDisplay();
  }

  void loop()
  {
    bool inputEvent = m_InputHelper.readInputs(millis());

    switch(m_deviceMode)
    {
      case DeviceMode::RUN: ProcessRun(); break;
      case DeviceMode::SETTINGS_MODE: ProcessSettingsRunMode(); break;
      case DeviceMode::SETTINGS_TIME: ProcessSwitchTime(); break;
      case DeviceMode::SETTINGS_BRIGHTNESS: ProcessBrightness(); break;
      case DeviceMode::TEST: ProcessTest(); break;
    }

    unsigned long deltaTime = millis() - m_PrevTime;
    m_PrevTime = millis();

    m_LEDRunner.update(deltaTime, m_Settings.SwitchTime, m_Settings.m_RunMode, m_Settings.m_TimeMode);
  }

  void runTest()
  {
    m_LEDRunner.runTest();
    m_DisplayHelper.runTest();
  }

private:

  static const uint8_t BTN_UP_SHORT_CLICKED = 1;
  static const uint8_t BTN_DOWN_SHORT_CLICKED = -1;
  static const uint8_t BTN_DOWN_UP_NO_SHORT_CLICKED = 0;

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

  void ProcessChangeMode()
  {
    bool mainButtonShortClicked = m_InputHelper.getButtonMain().IsNowShortClicked();
    if(!mainButtonShortClicked)
    return;

    m_DrawTitle = true;
    m_deviceMode = static_cast<DeviceMode>(wrapInt(static_cast<int>(m_deviceMode) + 1, 5)); 
    UpdateModeDisplay();
    if(m_deviceMode != DeviceMode::RUN)
    {
      m_LEDRunner.setRun(false);
    }
  }

  void UpdateModeDisplay()
  {
    switch(m_deviceMode)
    {
      case DeviceMode::RUN: m_DisplayHelper.DrawRunInfo(m_DrawTitle, m_LEDRunner.getRun()); break;
      case DeviceMode::SETTINGS_MODE: m_DisplayHelper.DrawSettingsRunModeInfo(m_DrawTitle, m_Settings.m_RunMode); break;
      case DeviceMode::SETTINGS_TIME: m_DisplayHelper.DrawSettingsTimeInfo(m_DrawTitle, m_Settings.SwitchTime / 10); break;
      case DeviceMode::SETTINGS_BRIGHTNESS: m_DisplayHelper.DrawSettingsBrightnessInfo(m_DrawTitle, m_Settings.Brightness); break;
      case DeviceMode::TEST: m_DisplayHelper.DrawTestInfo(m_DrawTitle); break;
    }  
  }

  int GetUpDownButtonsShortClicked()
  {
    bool upButtonShortClicked = m_InputHelper.getButtonUp().IsNowShortClicked();
    bool downButtonShortClicked = m_InputHelper.getButtonUp().IsNowShortClicked();
    if(upButtonShortClicked)
      return BTN_UP_SHORT_CLICKED;
    else if(downButtonShortClicked)
      return BTN_DOWN_SHORT_CLICKED;
    return BTN_DOWN_UP_NO_SHORT_CLICKED;
  }

  int GetUpDownButtonsHold()
  {
    bool upButtonHold = m_InputHelper.getButtonUp().IsHolded();
    bool downButtonHold = m_InputHelper.getButtonDown().IsHolded();
    return (upButtonHold - downButtonHold);
  }

  void ProcessRun()
  {
    ProcessChangeMode();
    int upDownButtons = GetUpDownButtonsShortClicked();
    if(upDownButtons == BTN_UP_SHORT_CLICKED)
    {
      m_LEDRunner.setRun(true);
      UpdateModeDisplay();
    }
    if(upDownButtons == BTN_DOWN_SHORT_CLICKED)
    {
      m_LEDRunner.setRun(false);
      UpdateModeDisplay();
    }
  }

  void ProcessSettingsRunMode()
  {
    ProcessChangeMode();
    int upDownButtons = GetUpDownButtonsShortClicked();
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_DrawTitle = false;
      m_Settings.switchRunMode(upDownButtons);
      UpdateModeDisplay();
    }
  }
    
  void ProcessSwitchTime()
  {
    ProcessChangeMode();

    int upDownButtons = GetUpDownButtonsShortClicked();
    int upDownHoldButtons = GetUpDownButtonsHold();
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_DrawTitle = false;
      m_Settings.setSwitchTime(m_Settings.SwitchTime + upDownButtons * 50);
      UpdateModeDisplay();
    }
    if(upDownHoldButtons != 0)
    {
      m_DrawTitle = false;
      m_Settings.setSwitchTime(m_Settings.SwitchTime + upDownHoldButtons * 50);
      UpdateModeDisplay();
    }
  }
    
  void ProcessBrightness()
  {
    ProcessChangeMode();

    int upDownButtons = GetUpDownButtonsShortClicked();
    int upDownHoldButtons = GetUpDownButtonsHold();
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_LEDRunner.setAllHigh();
      m_DrawTitle = false;
      m_Settings.setBrightness(m_Settings.Brightness + upDownButtons);
      m_LEDRunner.updateBrightness(m_Settings.Brightness);
      UpdateModeDisplay();
    }

    if(upDownHoldButtons != 0)
    {
      m_LEDRunner.setAllHigh();
      m_DrawTitle = false;
      m_Settings.setBrightness(m_Settings.Brightness + upDownHoldButtons);
      m_LEDRunner.updateBrightness(m_Settings.Brightness);
      UpdateModeDisplay();
    }
  }

  void ProcessTest()
  {
    ProcessChangeMode();
    int upDownButtons = GetUpDownButtonsShortClicked();
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      runTest();
    }
  }
};