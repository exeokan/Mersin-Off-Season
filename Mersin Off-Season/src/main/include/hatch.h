#include "Robot.h"
void Robot::hatch()
{
  double speed=0.2;
  if(js.GetRawButton(4))
  {  
    hatchMotor.Set(speed);
  }
  else if(js.GetRawButton(1))
  {
    hatchMotor.Set(-speed);
  }  
  else
  {
    hatchMotor.Set(0); 
  }
}