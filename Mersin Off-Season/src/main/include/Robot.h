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
  void tirmanma();
  void manuelHatch();
  double hatchPID();
  int getHatchPosition();
  void driveAssist(double angle);
  void updateSerialData();
  void calculateUltra();
  void Periodic();

  frc::Preferences *prefs=frc::Preferences::GetInstance();
  nt::NetworkTableEntry ntAngle;

  frc::Joystick js{1};

  frc::Talon solOn{2};    frc::Talon sagOn{0};//PWM
  frc::Talon solArka{2};  frc::Talon sagArka{3}; 

  frc::SpeedControllerGroup leftMotors{solOn,solArka};
  frc::SpeedControllerGroup rightMotors{sagOn,sagArka};
  frc::DifferentialDrive rd{rightMotors,leftMotors};

  VictorSPX tirmanma1{1};//CAN Bus
  VictorSPX tirmanma2{0};
  double tempTirmanma=0.0; //SmartDashboard verisi için-motorlara verilecek güç 

  frc::VictorSP hatchMotor{1};
  frc::Encoder hatchEncoder{0,1,true};

  bool goruyor;
  double lastAngle=0;
  double kp=0.0,kd=0.0,ki=0.0;//görüntü işleme için
  double errorI=0;

  bool assist=false,defans=false;
  bool hatchTasima=true;

  double hatchP,hatchI,hatchD;
  double hErrorI=0,hatchRef,lastError=0;
 
  frc::SerialPort serial{9600,frc::SerialPort::Port::kUSB1};
  char buffer[12];
  std::string dist;
  double aci=0.0;
  double distleft,distright;
  double leftArc,rightArc;
  bool ultrasonicException=false;

  double auto_kP=0.02;//! hesaplanmadı
  double goal;
  frc::ADIS16470_IMU gyro{};
};
