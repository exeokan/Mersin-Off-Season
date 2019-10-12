#include "Robot.h"
void Robot::driveAssist(double angle)
{
    double rot=0;
    if(goruyor){
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
    }
    double speed=js.GetRawAxis(3);//! değiştirilebilir
    rd.ArcadeDrive(speed,rot);
}