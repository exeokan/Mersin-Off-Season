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
  tempTirmanma=prefs->GetDouble("Tirmanma",0.5); //*tırmanma motorlarına verilecek hızı SmartDashboard'dan almak için
}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  assist=false;
}

void Robot::TeleopPeriodic() {
  double angle=ntAngle.GetDouble(777.0);//* raspberryden gelen açı değeri,777.0 default değer
  tirmanma();
  hatch();
  if(angle>700)
  {
    std::cout<<"gormuyor"<<std::endl;
    goruyor=false; 
  }
  else{
    std::cout << angle << std::endl;
    goruyor=true;
  }

  if(js.GetRawButtonPressed(2)){
  assist=!assist; 
  }

  if(!assist){
  rd.CurvatureDrive(-js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
  }
  else
  {
    std::cout << "Auto:ON" << std::endl; 
    driveAssist(angle);
  }
}  
void Robot::TestPeriodic() {
  
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
