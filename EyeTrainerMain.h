#include "Defines.h"
#include "DisplayHelper.h"
#include "Settings.h"
#include "LEDRunner.h"


class EyeTrainerMain
{
public:
  //==============================================================
  //state
  //==============================================================

  DeviceMode m_deviceMode;

  Settings m_Settings;
  LEDRunner m_LEDRunner;
  DisplayHelper m_DisplayHelper;

  //==============================================================
  //end of state
  //==============================================================

  EyeTrainerMain() { }

  void setup() 
  { 
      pinMode(LED_BUILTIN, OUTPUT);
      m_Settings = Settings();
      m_LEDRunner = LEDRunner(m_Settings);
      m_LEDRunner.setup();
      m_DisplayHelper = DisplayHelper();
      m_DisplayHelper.setup();
  }

  void loop()
  {

  }

  void runTest()
  {
    m_LEDRunner.runTest();
    m_DisplayHelper.runTest();
  }

private:

};