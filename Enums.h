#ifndef EYE_TRAINER_ENUMS
#define EYE_TRAINER_ENUMS 0

enum DeviceMode
{
  IDLE,
  SETTINGS_MODE,
  SETTINGS_BRIGHTNESS,
  SETTINGS_TIME,
  RUN, 
};

enum RunMode
{
  FORWARD,
  BACKWARD,
  BOTH,
  RANDOM,
  TEST
};

enum TimeMode
{
  CONST,
  MANUAL,
  INCREASING
};

#endif