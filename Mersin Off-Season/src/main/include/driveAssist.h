#include "Robot.h"
#include <iostream>

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
    speed=js.GetRawAxis(1);
    rd.ArcadeDrive(speed,rot);
  }
  else if(!goruyor && js.GetRawButton(8))
  {
    speed=js.GetRawAxis(1);
    rd.ArcadeDrive(speed,rot);
  }
  else if(js.GetRawButtonPressed(7))
  {
    ultrasonicException=false;
    calculateUltra();
  }
  else if(js.GetRawButton(7))
  {
      if(ultrasonicException)
      {
        //!ALERT
      }
      else if(leftArc > rightArc)
      {
      float current = ecDrive_right.Get()/1024*48;
      float rightSet = (rightArc-current)*auto_kP;
      if(rightSet > 1){
        rightSet = 1;
      }
      float leftSet = leftArc/rightArc * rightSet;
      
      solOn.Set(leftSet);
      solArka.Set(leftSet);
      sagOn.Set(rightSet*-1.0);
      sagArka.Set(rightSet*-1.0);
      }
      else if(rightArc > leftArc){
      float current = ecDrive_right.Get()/1024*48;
      float rightSet = (rightArc-current)*auto_kP;
      if(rightSet > 1){
        rightSet = 1;
      }
      float leftSet = leftArc/rightArc * rightSet;
      
      solOn.Set(leftSet);
      solArka.Set(leftSet);
      sagOn.Set(rightSet*-1.0);
      sagArka.Set(rightSet*-1.0);
      }
  }
}

void Robot::calculateUltra()
{
  if(distleft==distright)
  {
    std::cout<<"mesafeler esit"<<std::endl; //!drive 
    ultrasonicException=true;
  }
  else if(distleft>distright)
  {
    double x=45*distright/(distleft-distright);
    leftArc=45+x+2; // 2=ultrasonik teker arası
    leftArc=leftArc*aci;

    rightArc=x-2;
    rightArc=rightArc*aci;
    ecDrive_right.Reset();
  } 
  else
  {
    double x=45*distleft/(distright-distleft);
    rightArc=45+x+2; // 2=ultrasonik teker arası
    leftArc=x-2;
    ecDrive_right.Reset();
  }   
}
