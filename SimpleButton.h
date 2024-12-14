#ifndef EYE_TRAINER_SIMPLEBUTTON
#define EYE_TRAINER_SIMPLEBUTTON 0

class SimpleButton
{
public:

  SimpleButton(int _ButtonPin, unsigned long _LongClickTime)
  {
    m_LongClickTime = _LongClickTime;
    m_ButtonPin = _ButtonPin;
  }

  void setup()
  {
    pinMode(m_ButtonPin, INPUT);  
  }

  int update(unsigned long _Time)
  {
    clearClicks();

    int prevState = m_State;

    unsigned long deltaTime = _Time - m_PrevTimeMS;
    m_PrevTimeMS = _Time;
    bool pinState = digitalRead(m_ButtonPin);

    if(m_State == PRESSED && pinState)
    {
      m_PressedTime += deltaTime;
      if(m_PressedTime >= m_LongClickTime)
      {
        m_IsNowHolded = true;
      }
    }
    else if(m_State == PRESSED && !pinState)
    {
      m_State = RELEASED;
      m_IsNowClicked = true;
      
      if(m_PressedTime >= m_LongClickTime)
      {
        m_IsNowLongClicked = true;
        m_PressedTime = 0;
      }
      else
      {
        m_IsNowShortClicked = true;
      }
    }
    else if(m_State == RELEASED && pinState)
    {
      m_State = PRESSED;
      m_IsNowPressed = true;  
    }

    return m_IsNowHolded | (prevState != m_State);
  }

  bool IsNowClicked()
  {
    return m_IsNowClicked;
  }

  bool IsNowPressed()
  {
    return m_IsNowPressed;
  }

  bool IsNowReleased()
  {
    return m_IsNowReleased;
  }

  bool IsHolded()
  {
    return m_IsNowHolded;
  }

  bool IsNowLongClicked()
  {
    return m_IsNowLongClicked;
  }

  bool IsNowShortClicked()
  {
    return m_IsNowShortClicked;
  }

  unsigned long GetPressedTime()
  {
    return m_PressedTime;
  }

private:
  static const int CLICK_DELAY = 20;
  static const int PRESSED = 1;
  static const int RELEASED = 0;
  int m_ButtonPin;
  int m_State = RELEASED;
  unsigned long m_PrevTimeMS = 0;
  unsigned long m_PressedTime = 0;
  unsigned long m_LongClickTime = 250;
  unsigned long m_PressDelayTime = 0;
  unsigned long m_ReleaseDelayTime = 0;
  bool m_IsNowClicked = false;
  bool m_IsNowPressed = false;
  bool m_IsNowReleased = false;
  bool m_IsNowHolded = false;
  bool m_IsNowShortClicked = false;
  bool m_IsNowLongClicked = false;

  void clearClicks()
  {
    m_IsNowClicked = false;
    m_IsNowPressed = false;
    m_IsNowReleased = false;
    m_IsNowReleased = false;
    m_IsNowHolded = false;
    m_IsNowShortClicked = false;
    m_IsNowLongClicked = false;
  }
};

#endif