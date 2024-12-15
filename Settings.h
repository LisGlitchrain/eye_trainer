#ifndef EYE_TRAINER_SETTINGS
#define EYE_TRAINER_SETTINGS 0

#include "Defines.h"
#include "Enums.h"

class Settings
{
public:
  enum  RunMode  RunModeState  = RunMode::RANDOM;
  enum  TimeMode TimeModeState = TimeMode::CONST;
  int            SwitchTime = 3000; //In milliseconds
  float          Brightness = MAX_BRIGHTNESS / 2;

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
    RunModeState = RunMode::FORWARD;
  }

  void switchRunMode(int _ModeIncrement)
  {
    RunModeState = static_cast<RunMode>(wrapInt(static_cast<int>(RunModeState) + _ModeIncrement, 4));
  }

  void setTimeMode(enum TimeMode _TimeMode)
  {
    TimeModeState = _TimeMode;
  }

  void switchTimeMode(int _ModeIncrement)
  {
    TimeModeState = static_cast<TimeMode>(wrapInt(static_cast<int>(TimeModeState) + _ModeIncrement, 3));
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