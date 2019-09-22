/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
  nt::NetworkTableEntry ntAngle;
void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  auto inst=nt::NetworkTableInstance::GetDefault();
  auto table=inst.GetTable("ChickenVision");
  ntAngle=table->GetEntry("HedefAci");

  ultraLeft.SetAutomaticMode(true);
  ultraRight.SetAutomaticMode(true);
  gyro.Calibrate();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  kp=prefs->GetDouble("KP",0.00);
  kd=prefs->GetDouble("KD",0.0);
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
 
}

void Robot::AutonomousPeriodic() {
  double distRight=ultraRight.GetRangeMM()/10.0;
  double distLeft=ultraLeft.GetRangeMM()/10.0;
  std::cout<<"DistRight:"<<distRight<<" DistLeft:"<<distLeft<<std::endl;
}

void Robot::TeleopInit() {
  assist=false;
}

void Robot::TeleopPeriodic() {
  double angle=ntAngle.GetDouble(777.0);
  if(angle>700)
  {
    std::cout<<"gormuyor"<<std::endl;
    angle=lastAngle;
  
  }
  else{
    std::cout << angle << std::endl;
  }

  if(js.GetRawButtonPressed(1))
  assist=!assist;

  if(!assist)
  rd.CurvatureDrive(-js.GetRawAxis(1),js.GetRawAxis(4),js.GetRawButton(5));
  else
  {
    std::cout << "Auto:ON" << std::endl;
    std::cout << kp <<kd <<std::endl;
    double rot=(angle/30.0)*kp+(angle/30.0-lastAngle)*kd;
    lastAngle=(angle/30.0);
    double speed=-js.GetRawAxis(1);
    rd.ArcadeDrive(speed,rot);
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
