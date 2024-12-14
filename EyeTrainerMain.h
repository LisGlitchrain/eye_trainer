#include "Defines.h"
#include "DisplayHelper.h"
#include "Settings.h"
#include "LEDRunner.h"
#include "InputHelper.h"

class EyeTrainerMain
{
public:
  //==============================================================
  //state
  //==============================================================

  DeviceMode m_deviceMode;

  Settings m_Settings = Settings();
  LEDRunner m_LEDRunner = LEDRunner(&m_Settings);
  DisplayHelper m_DisplayHelper = DisplayHelper(&m_Settings);
  InputHelper m_InputHelper = InputHelper();

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
  }

  void loop()
  {
    bool inputEvent = m_InputHelper.readInputs(millis());
    
  }

  void runTest()
  {
    m_LEDRunner.runTest();
    m_DisplayHelper.runTest();
  }

private:

};