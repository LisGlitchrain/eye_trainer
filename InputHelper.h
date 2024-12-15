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

  int getUpDownButtonsShortClicked()
  {
    bool upButtonShortClicked = m_UpButton.isNowShortClicked();
    bool downButtonShortClicked = m_DownButton.isNowShortClicked();
    if(upButtonShortClicked)
      return BTN_UP_SHORT_CLICKED;
    else if(downButtonShortClicked)
      return BTN_DOWN_SHORT_CLICKED;
    return BTN_DOWN_UP_NO_SHORT_CLICKED;
  }

  int getUpDownButtonsHold()
  {
    bool upButtonHold   = m_UpButton.isHolded();
    bool downButtonHold = m_DownButton.isHolded();
    if(upButtonHold)
      return BTN_UP_HOLDED;
    else if(downButtonHold)
      return BTN_DOWN_HOLDED;
    return BTN_DOWN_UP_NOT_HOLDED;
  }

private:
  bool m_InputEvent;
  
  SimpleButton m_MainButton = SimpleButton(PIN_BTN_MAIN, LONG_CLICK_TIME_MS);
  SimpleButton m_UpButton   = SimpleButton(PIN_BTN_UP, LONG_CLICK_TIME_MS);
  SimpleButton m_DownButton = SimpleButton(PIN_BTN_DOWN, LONG_CLICK_TIME_MS);
};

#endif