#ifndef EYE_TRAINER_ENUMS
#define EYE_TRAINER_ENUMS 0

enum DeviceMode
{
  RUN = 0, 
  SETTINGS_MODE,
  SETTINGS_BRIGHTNESS,
  SETTINGS_TIME_SWITCH,
  SETTINGS_TIME_MODE,
  TEST
};

enum RunMode
{
  FORWARD = 0,
  BACKWARD = 1,
  BOTH = 2,
  RANDOM = 3
};

enum TimeMode
{
  CONST = 0,
  MANUAL,
  DECREASING // not implemented
};

#endif