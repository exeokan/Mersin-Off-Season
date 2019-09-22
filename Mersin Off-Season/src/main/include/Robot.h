/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <frc/WPILib.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "ADIS16470_IMU.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTableEntry.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  
  private:

  frc::Preferences *prefs=frc::Preferences::GetInstance();;
  double kp=0.0,kd=0.0;
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::DoubleSolenoid pnueTest{0,1};
  frc::Joystick js{0};

  frc::ADIS16470_IMU gyro{};
  frc::Ultrasonic ultraLeft{6,8};
  frc::Ultrasonic ultraRight{7,9};

  frc::Talon solOn{1};  frc::Talon solArka{0}; 
  frc::Talon sagOn{2};  frc::Talon sagArka{3}; 

  //frc::RobotDrive autoRd{solOn, solArka,sagOn,sagArka}; 

  frc::SpeedControllerGroup left{solOn,solArka};
  frc::SpeedControllerGroup right{sagOn,sagArka};
  frc::DifferentialDrive rd{left,right};
  double lastAngle=0;
  bool assist=false;

  
};
