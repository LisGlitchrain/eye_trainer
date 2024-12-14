#include "Defines.h"
#include "Enums.h"

class Settings
{
public:
  enum     RunMode  m_RunMode = RunMode::Random;
  enum     TimeMode m_TimeMode = TimeMode::Const;
  float    SwitchTime = 3;

  Settings()
  {
  }
};