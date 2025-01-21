#ifndef EYE_TRAINER_SETTINGS
#define EYE_TRAINER_SETTINGS 0

#include "Defines.h"
#include "Enums.h"

class Settings
{
public:
  enum  RunMode  RunModeState  = RunMode::PING_PONG;
  enum  TimeMode TimeModeState = TimeMode::CONST;
  int            SwitchTime = DEFAULT_SWITCH_TIME; //In milliseconds
  float          Brightness = MAX_BRIGHTNESS / 2;
  float          LED_DISTANCE_ARRAY;

  //=======================================
  //Singleton. AVOID COPY ASSIGNMENTS
  //=======================================

  static Settings& getInstance()
  {
    static Settings instance; // Guaranteed to be destroyed. Instantiated on first use.
    return instance;  
  }

  Settings() {}
  Settings(Settings const&)          = delete;
  void operator = (Settings const&)  = delete;

  //=======================================
  //Singleton. AVOID COPY ASSIGNMENTS
  //=======================================

  void setSwitchTime(int _SwitchTime)
  {
    if(_SwitchTime > MAX_SWITCH_TIME)
    {
      SwitchTime = MAX_SWITCH_TIME;
      return;
    }
    if(_SwitchTime < MIN_SWITCH_TIME)
    {
      SwitchTime = MIN_SWITCH_TIME;
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

  int getDisplaySwitchTime()
  {
    return SwitchTime / 10;
  }

  int getDistanceCorrectedSwitchTime(int _LedIndex)
  {
    return (int) (min(max(SwitchTime * LedDistances[_LedIndex], MIN_SWITCH_TIME), MAX_SWITCH_TIME));
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