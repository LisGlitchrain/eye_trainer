#ifndef EYE_TRAINER_SETTINGS
#define EYE_TRAINER_SETTINGS 0

#include "Defines.h"
#include "Enums.h"

class Settings
{
public:
  enum  RunMode  m_RunMode = RunMode::RANDOM;
  enum  TimeMode m_TimeMode = TimeMode::CONST;
  int   SwitchTime = 3000; //In milliseconds
  // float   Brightness = MAX_BRIGHTNESS;
  float   Brightness = 195;

  Settings()
  {
  }

  void setSwitchTime(int _SwitchTime)
  {
    if(_SwitchTime > 15000)
    {
      SwitchTime = 15000;
      return;
    }
    if(_SwitchTime < 250)
    {
      SwitchTime = 250;
      return;
    }

    SwitchTime = _SwitchTime;
  }

  void setBrightness(float _Brightness)
  {
    if(_Brightness > MAX_BRIGHTNESS)
    {
      Brightness = MAX_BRIGHTNESS;
      return;
    }
    if(_Brightness < MIN_BRIGHTNESS)
    {
      Brightness = MIN_BRIGHTNESS;
      return;
    }
    Brightness = _Brightness;
  }

  void resetRunMode(RunMode _RunMode)
  {
    m_RunMode = RunMode::FORWARD;
  }

  void switchRunMode(int _NextOrBack)
  {
    if(m_RunMode == RunMode::FORWARD)
    {
      m_RunMode = RunMode::BACKWARD;
    }
    else if(m_RunMode == RunMode::BACKWARD)
    {
      m_RunMode = RunMode::BOTH;
    }
    else if(m_RunMode == RunMode::BOTH)
    {
      m_RunMode = RunMode::RANDOM;
    }
    else if(m_RunMode == RunMode::RANDOM)
    {
      m_RunMode = RunMode::FORWARD;
    }

    // RunMode newRunMode = static_cast<RunMode>(wrapInt(static_cast<int>(m_RunMode) + _NextOrBack, 4));
    // m_RunMode = newRunMode;
  }

  void setTimeMode(enum TimeMode _TimeMode)
  {
    m_TimeMode = _TimeMode;
  }



private:
  int wrapInt(int _Num,  int _Max)
  {
    if(_Num < 0)
    {
      return (_Max + _Num % _Max);
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

};

#endif