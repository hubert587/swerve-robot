/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <rev/CANSparkMax.h>
#include <rev/SparkMax.h>
#include <frc/commands/Subsystem.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Solenoid.h>
//#include <adi/ADIS16448_IMU.h>



class Drivetrain : public frc::Subsystem {
 private:
 
//Defines Solenoid
frc::DoubleSolenoid DrivetrainSolenoid{0,1};
frc::Solenoid RampExtendSolenoid{2};

//Defines Gyroscope
//frc::ADIS16448_IMU m_imu{frc::ADIS16448_IMU::kZ, frc::ADIS16448_IMU::kComplementary, frc::SPI::kMXP};

//Defines Four Motor Controllers
rev::CANSparkMax FrontLeftMotor{ 1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
rev::CANSparkMax RearLeftMotor{ 2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
rev::CANSparkMax FrontRightMotor{ 3, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
rev::CANSparkMax RearRightMotor{ 4, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

//Define Mecanum Drive
frc::MecanumDrive MecanumTime{ FrontLeftMotor, RearLeftMotor, FrontRightMotor, RearRightMotor};

//Define Differential Drive and Followers
//frc::DifferentialDrive TankTime{ FrontLeftMotor, FrontRightMotor};

//Defines Differential Drive and Motor Groupings
frc::DifferentialDrive TankTimeFront{ FrontLeftMotor, FrontRightMotor};
frc::DifferentialDrive TankTimeRear{ RearLeftMotor, RearRightMotor};

static bool driveModeDifferential;


 public:

  void Drive();
  Drivetrain();
  void InitDefaultCommand() override;
  
};
