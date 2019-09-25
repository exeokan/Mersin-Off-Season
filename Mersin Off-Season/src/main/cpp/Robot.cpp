/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* KelRot#5655 Deep Space Code for Mersin Off-Season                          */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <math.h>

#include <iostream>

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
  tempTirmanma=prefs->GetDouble("Tirmanma",0.0); //*tırmanma motorlarına verilecek hızı SmartDashboard'dan almak için
}
void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {//! şuan sadece tırmanma denemek için 
  rd.CurvatureDrive(-js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
  if(js.GetRawButton(1))
  {
    tirmanma1.Set(ControlMode::PercentOutput,tempTirmanma);
    tirmanma2.Set(ControlMode::PercentOutput,tempTirmanma);
    std::cout<<tempTirmanma<<std::endl;
  }
  else if(js.GetRawButton(2))
  {
    tirmanma1.Set(ControlMode::PercentOutput,-tempTirmanma);
    tirmanma2.Set(ControlMode::PercentOutput,-tempTirmanma);
    std::cout<<tempTirmanma<<std::endl;
  }
  else{
    tirmanma1.Set(ControlMode::PercentOutput,0.0);
    tirmanma2.Set(ControlMode::PercentOutput,0.0);
    
  }
}

void Robot::TeleopInit() {
  assist=false;
}

void Robot::TeleopPeriodic() {
  double angle=ntAngle.GetDouble(777.0);//* raspberryden gelen açı değeri,777.0 default değer
  if(angle>700)
  {
    std::cout<<"gormuyor"<<std::endl;
    goruyor=false; 
  }
  else{
    std::cout << angle << std::endl;
    goruyor=true;
  }

  if(js.GetRawButtonPressed(1)){
  assist=!assist; 
  }

  if(!assist){
  rd.CurvatureDrive(-js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
  }
  else
  {
    std::cout << "Auto:ON" << std::endl;
    double rot=0;
    if(goruyor){
      double errorP =(angle/30.0);
      double errorD = (angle/30.0-lastAngle);
      lastAngle= (angle/30.0);
      if(abs(angle) <= 8.0 && abs(angle)>0.5){
        errorI += errorP;
      }
      else{//* aralıkta değil ise hesaplama
        errorI=0;
      }
      //* integrali sınırlama
      if(errorI>  50/ki){
        errorI = 50/ki;
      }
      else if(errorI< -50/ki){
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
    double speed=-js.GetRawAxis(1);
    rd.ArcadeDrive(speed,rot);
  }
}

void Robot::TestPeriodic() {
  
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
