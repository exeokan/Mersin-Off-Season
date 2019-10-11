/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* KelRot#5655 Deep Space Code for Mersin Off-Season                          */
/*----------------------------------------------------------------------------*/

#include <math.h>
#include "driveAssist.h"
#include "hatch.h"
#include "tirmanma.h"

#include <iostream>
#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

  void Robot::RobotInit() {
  auto inst=nt::NetworkTableInstance::GetDefault();
  auto table=inst.GetTable("ChickenVision");
  ntAngle=table->GetEntry("HedefAci");
}

void Robot::RobotPeriodic() {
  kp=prefs->GetDouble("KP",0.00);
  kd=prefs->GetDouble("KD",0.0);
  ki=prefs->GetDouble("KI",0.0);

  hatchP=prefs->GetDouble("Hatch P",0.0);
  hatchI=prefs->GetDouble("Hatch I",0.0);
  hatchD=prefs->GetDouble("Hatch D",0.0);

  tempTirmanma=prefs->GetDouble("Tirmanma",0.5); //*tırmanma motorlarına verilecek hızı SmartDashboard'dan almak için
}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  hatchEncoder.Reset(); //!
  assist=false;
  hatchRef=150;
  autoHatch=false;
}

void Robot::TeleopPeriodic() {
  double angle=ntAngle.GetDouble(777.0);//* raspberryden gelen açı değeri,777.0 default değer
  std::cout<<getHatchPosition()<<std::endl;
  tirmanma();
  if(angle>700)
  {
    std::cout<<"gormuyor"<<std::endl;
    goruyor=false; 
  }
  else{
    std::cout << angle << std::endl;
    goruyor=true;
  }

  if(js.GetRawAxis(3)>0){
    assist=!assist; 
  }
  if(js.GetRawButtonPressed(7))//Back tuşu
  {
    reversedDrive= !reversedDrive;//sürüşü tersine çevirir(line 90)
  }
  if(!assist){
    if(reversedDrive)
    rd.CurvatureDrive(js.GetRawAxis(1),-js.GetRawAxis(4),js.GetRawButton(5));
    else
    rd.CurvatureDrive(-js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
  }
  else
  {
    std::cout << "Auto:ON" << std::endl; 
    driveAssist(angle);
  }

 if(js.GetRawButtonPressed(8))
  {
    if(distleft==distright)
    {
      std::cout<<"mesafeler esit"<<std::endl; //drive
    }
    else if(distleft>distright)
    {
      double x=28*distright/(distleft-distright);
      leftArc=28+x+2; // 2=ultrasonik teker arası
      leftArc=leftArc*aci;

      rightArc=x-2;
      rightArc=rightArc*aci;
      hizala= !hizala; 
    } 
    else
    {
      double x=28*distleft/(distright-distleft);
      rightArc=28+x+2; // 2=ultrasonik teker arası
      leftArc=x-2;
      hizala= !hizala; 
    }   

  }
  if(hizala){
      if(leftArc > rightArc){//gidecekleri değerler değil
      float current = ecDrive_left.Get()/1024*48;
      float leftSet = (leftArc-current)*auto_kP;
      if(leftSet > 1){
        leftSet = 1;
      }
      float rightSet = rightArc/leftArc * leftSet;
      
      solOn.Set(leftSet);
      solArka.Set(leftSet);
      sagOn.Set(rightSet*-1.0);
      sagArka.Set(rightSet*-1.0);
    }
    if(rightArc > leftArc){
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
void Robot::TestPeriodic() {
  
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
