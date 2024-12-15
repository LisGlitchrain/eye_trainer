#include "Defines.h"
#include "DisplayHelper.h"
#include "Settings.h"
#include "LEDRunner.h"
#include "InputHelper.h"
#include "Enums.h"
#include "WrapHelper.h"

class EyeTrainerMain
{
public:
  EyeTrainerMain() { }

  void setup() 
  { 
      pinMode(LED_BUILTIN, OUTPUT);
      m_LEDRunner.setup();
      m_DisplayHelper.setup();
      m_InputHelper.setup();
      updateModeDisplay();
  }

  void loop()
  {
    bool inputEvent = m_InputHelper.readInputs(millis());
    
    if(inputEvent)
    {
      processChangeMode();
      int upDownButtonsShortClickState = m_InputHelper.getUpDownButtonsShortClicked();
      int upDownButtonsHoldState = m_InputHelper.getUpDownButtonsHold();
      switch(m_deviceMode)
      {
        case DeviceMode::RUN:                  processRun(upDownButtonsShortClickState, upDownButtonsHoldState);             break;
        case DeviceMode::SETTINGS_MODE:        processSettingsRunMode(upDownButtonsShortClickState, upDownButtonsHoldState); break;
        case DeviceMode::SETTINGS_TIME_SWITCH: processSwitchTime(upDownButtonsShortClickState, upDownButtonsHoldState);      break;
        case DeviceMode::SETTINGS_BRIGHTNESS:  processBrightness(upDownButtonsShortClickState, upDownButtonsHoldState);      break;
        case DeviceMode::SETTINGS_TIME_MODE:   processTimeMode(upDownButtonsShortClickState, upDownButtonsHoldState);        break;
        case DeviceMode::TEST:                 processTest(upDownButtonsShortClickState, upDownButtonsHoldState);            break;
      }
    }
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - m_PrevTime;
    m_PrevTime = currentTime;
    m_LEDRunner.update(deltaTime);
  }

  void runTest()
  {
    m_LEDRunner.runTest();
    m_DisplayHelper.runTest();
  }

private:
  enum DeviceMode m_deviceMode  = DeviceMode::RUN;

  LEDRunner     m_LEDRunner     = LEDRunner();
  DisplayHelper m_DisplayHelper = DisplayHelper();
  InputHelper   m_InputHelper   = InputHelper();
  unsigned long m_PrevTime      = 0;

  void updateModeDisplay()
  {
    m_DisplayHelper.UpdateModeDisplay(m_LEDRunner.getRun(), m_deviceMode);
  }

  void processChangeMode()
  {
    bool mainButtonShortClicked = m_InputHelper.getButtonMain().isNowShortClicked();
    if(!mainButtonShortClicked)
    return;

    m_DisplayHelper.setDrawTitle(true);
    m_deviceMode = static_cast<DeviceMode>(wrapInt(static_cast<int>(m_deviceMode) + 1, 6)); 
    updateModeDisplay();
    if(m_deviceMode != DeviceMode::RUN)
    {
      m_LEDRunner.setRun(false);
    }
  }

  void processRun(int upDownButtons, int upDownButtonsHold)
  {
    if(Settings::getInstance().TimeModeState == TimeMode::MANUAL && upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_LEDRunner.manualUpdate(Settings::getInstance().RunModeState, upDownButtons);
    }
    else
    {
      if(upDownButtons == BTN_UP_SHORT_CLICKED)
      {
        m_DisplayHelper.setDrawTitle(false);
        m_LEDRunner.setRun(true);
        updateModeDisplay();
      }
      if(upDownButtons == BTN_DOWN_SHORT_CLICKED)
      {
        m_DisplayHelper.setDrawTitle(false);
        m_LEDRunner.setRun(false);
        updateModeDisplay();
      }
    }
  }

  void processSettingsRunMode(int upDownButtons, int upDownButtonsHold)
  {
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_DisplayHelper.setDrawTitle(false);
      Settings::getInstance().switchRunMode(upDownButtons);
      updateModeDisplay();
    }
  }
    
  void processSwitchTime(int upDownButtons, int upDownButtonsHold)
  {
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_DisplayHelper.setDrawTitle(false);
      Settings::getInstance().setSwitchTime(Settings::getInstance().SwitchTime + upDownButtons * 50);
      updateModeDisplay();
    }
    if(upDownButtonsHold != BTN_DOWN_UP_NOT_HOLDED)
    {
      m_DisplayHelper.setDrawTitle(false);
      Settings::getInstance().setSwitchTime(Settings::getInstance().SwitchTime + upDownButtonsHold * 50);
      updateModeDisplay();
    }
  }
    
  void processBrightness(int upDownButtons, int upDownButtonsHold)
  {
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_LEDRunner.setAllHigh();
      m_DisplayHelper.setDrawTitle(false);
      Settings::getInstance().setBrightness(Settings::getInstance().Brightness + upDownButtons);
      m_LEDRunner.setBrightness(Settings::getInstance().Brightness);
      updateModeDisplay();
    }

    if(upDownButtonsHold != BTN_DOWN_UP_NOT_HOLDED)
    {
      m_LEDRunner.setAllHigh();
      m_DisplayHelper.setDrawTitle(false);
      Settings::getInstance().setBrightness(Settings::getInstance().Brightness + upDownButtonsHold);
      m_LEDRunner.setBrightness(Settings::getInstance().Brightness);
      updateModeDisplay();
    }
  }

  void processTimeMode(int upDownButtons, int upDownButtonsHold)
  {
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      m_DisplayHelper.setDrawTitle(false);
      Settings::getInstance().switchTimeMode(upDownButtons);
      updateModeDisplay();
    }
  }

  void processTest(int upDownButtons, int upDownButtonsHold)
  {
    if(upDownButtons != BTN_DOWN_UP_NO_SHORT_CLICKED)
    {
      runTest();
    }
  }
};