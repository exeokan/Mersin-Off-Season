/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* KelRot#5655 Deep Space Code for Mersin Off-Season                          */
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
#include "ctre/Phoenix.h"
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
  frc::Preferences *prefs=frc::Preferences::GetInstance();
  nt::NetworkTableEntry ntAngle;

  frc::Joystick js{0};

  frc::Talon solOn{1};    frc::Talon sagOn{2};
  frc::Talon solArka{0};  frc::Talon sagArka{3}; 

  VictorSPX tirmanma1{0};
  VictorSPX tirmanma2{1};
  double tempTirmanma=0.0; //SmartDashboard verisi için-motorlara verilecek güç 

  frc::SpeedControllerGroup left{solOn,solArka};
  frc::SpeedControllerGroup right{sagOn,sagArka};
  
  frc::DifferentialDrive rd{left,right};

  bool goruyor;
  double lastAngle=0;
  double kp=0.0,kd=0.0,ki=0.0;
  double errorI=0;
  bool assist=false;
};
