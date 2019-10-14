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
#include "SerialCom.h"
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
  hatchEncoder.Reset();
  assist=false;
  hatchRef=75;
  autoHatch=false;
}

void Robot::TeleopPeriodic() {
  double angle=ntAngle.GetDouble(777.0);//* raspberryden gelen açı değeri,777.0 default değer
  tirmanma();
  updateSerialData();
  //Drive Assist
  if(angle>700)
  {
    std::cout<<"gormuyor"<<std::endl;
    goruyor=false; 
  }
  else{
    std::cout <<"Goruntu isleme aci="<< angle << std::endl;
    goruyor=true;
  } 
  if(js.GetRawButtonPressed(8)){//Drive Assist açma
    assist=!assist; 
  }
  if(js.GetRawButtonPressed(7)){//Back tuşu -tırmanma ve defans modu
    reversedDrive= !reversedDrive;//sürüşü tersine çevirir(line 90)
    hatchRef=0;
  }
  if(!assist){
    if(reversedDrive)
    rd.CurvatureDrive(js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
    else
    rd.CurvatureDrive(-js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
  }
  else
  {
    std::cout << "Auto:ON" << std::endl; 
    driveAssist(angle);
  }

  //* Hatch
  if(js.GetRawButtonPressed(2))
  {
    hatchTasima= !hatchTasima;
    if(hatchTasima)
    hatchRef=75;
    else
    hatchRef=150;
  }
 // hatchMotor.Set(hatchPID());
} 
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
