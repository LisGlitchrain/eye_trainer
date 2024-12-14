#ifndef EYE_TRAINER_INPUTHELPER
#define EYE_TRAINER_INPUTHELPER 0

#include "Defines.h"
#include "SimpleButton.h"

class InputHelper
{
public:
  InputHelper() { }

  void setup()
  {
    m_MainButton.setup();
    m_UpButton.setup();
    m_DownButton.setup();
  }

  bool readInputs(unsigned long _Time)
  {
    m_InputEvent = false;

    m_InputEvent |= m_MainButton.update(_Time);
    m_InputEvent |= m_UpButton.update(_Time);
    m_InputEvent |= m_DownButton.update(_Time);

    return m_InputEvent;
  }

  SimpleButton getButtonMain()
  {
    return m_MainButton;
  }

  SimpleButton getButtonUp()
  {
    return m_UpButton;
  }

  SimpleButton getButtonDown()
  {
    return m_DownButton;
  }

private:
  bool m_InputEvent;
  
  SimpleButton m_MainButton = SimpleButton(PIN_BTN_MAIN, LONG_CLICK_TIME_MS);
  SimpleButton m_UpButton = SimpleButton(PIN_BTN_UP, LONG_CLICK_TIME_MS);
  SimpleButton m_DownButton = SimpleButton(PIN_BTN_DOWN, LONG_CLICK_TIME_MS);
};

#endif