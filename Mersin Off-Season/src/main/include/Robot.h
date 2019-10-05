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

  void tirmanma();
  void hatch();
  void driveAssist(double angle);
  private:
  frc::Preferences *prefs=frc::Preferences::GetInstance();
  nt::NetworkTableEntry ntAngle;

  frc::Joystick js{0};

  frc::Talon solOn{2};    frc::Talon sagOn{0};//PWM
  frc::Talon solArka{2};  frc::Talon sagArka{3}; 

  frc::SpeedControllerGroup left{solOn,solArka};
  frc::SpeedControllerGroup right{sagOn,sagArka};
  frc::DifferentialDrive rd{left,right};

  VictorSPX tirmanma1{1};//CAN Bus
  VictorSPX tirmanma2{0};
  double tempTirmanma=0.0; //SmartDashboard verisi için-motorlara verilecek güç 
  frc::VictorSP hatchMotor{1};//! kontrol et

  bool goruyor;
  double lastAngle=0;
  double kp=0.0,kd=0.0,ki=0.0;
  double errorI=0;
  bool assist=false;
  
};
