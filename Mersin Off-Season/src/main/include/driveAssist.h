#include "Robot.h"
#include <iostream>
#define PI 3.14159265358979323846
void Robot::driveAssist(double angle)
{
  double rot=0,speed;
  if(goruyor && js.GetRawButton(8)){
    double errorP =(angle/30.0);
    double errorD = (angle/30.0-lastAngle);
    lastAngle= (angle/30.0);
    if(abs(angle) <= 8.0 && abs(angle)>0.5){
      errorI += errorP;
    }
    else{//* aralıkta değil I'yı ise hesaplama
      errorI=0;
    }
    //* integral sınırı
    if(errorI > 50/ki){
      errorI = 50/ki;
    }
    else if(errorI < -50/ki){
      errorI = -50/ki;
    }
    rot= errorP*kp + errorI*ki + errorD*kd;
    if(rot>=1.00)
    {
      rot= 1.0;
    }
    else if(rot<=-1.0)
    {
      rot= -1.0;
    }
    speed=-js.GetRawAxis(1);
    rd.ArcadeDrive(speed,rot);
  }
  else if(!goruyor && js.GetRawButton(8))
  {
    speed=-js.GetRawAxis(1);
    rd.ArcadeDrive(speed,rot);
  }
  else if(js.GetRawButtonPressed(7))
  {
    goal=aci*(180/PI);
    gyro.Reset();
  }
  else if(js.GetRawButton(7))
  {
    double error=goal-gyro.GetAngle();
    std::cout<<error<<gyro.GetAngle()<<std::endl;
    rd.ArcadeDrive(0,error*-0.2);
  }
  
}
