#include "EyeTrainerMain.h"

EyeTrainerMain m_EyeTrainerMain;

void setup() 
{ 
    m_EyeTrainerMain = EyeTrainerMain();
    m_EyeTrainerMain.setup();
}

void loop()
{
  m_EyeTrainerMain.loop();
}