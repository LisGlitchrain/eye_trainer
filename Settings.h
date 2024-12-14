#ifndef EYE_TRAINER_SETTINGS
#define EYE_TRAINER_SETTINGS 0

#include "Defines.h"
#include "Enums.h"

class Settings
{
public:
  enum  RunMode  m_RunMode = RunMode::RANDOM;
  enum  TimeMode m_TimeMode = TimeMode::CONST;
  float SwitchTime = 3; //In seconds
  bool  Changed = true;

  Settings()
  {
  }
};

#endif