#include "Robot.h"

void Robot::tirmanma()
{  
  if(js.GetPOV()==0)
  {
    tirmanma1.Set(ControlMode::PercentOutput,tempTirmanma);
    tirmanma2.Set(ControlMode::PercentOutput,tempTirmanma);
  }
  else if (js.GetPOV()==180) {
    tirmanma1.Set(ControlMode::PercentOutput,-0.2);
    tirmanma2.Set(ControlMode::PercentOutput,-0.2);
  }
  else
  {
    tirmanma1.Set(ControlMode::PercentOutput,0.0);
    tirmanma2.Set(ControlMode::PercentOutput,0.0);
  }
}