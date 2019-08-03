/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>

class Beak : public frc::Subsystem {
 private:

  int Position;
  frc::Solenoid BeakOpenSolenoid{5};
  frc::Solenoid BeakExtendSolenoid{4};

  frc::Solenoid BallIntakeSolenoid{6};
  WPI_TalonSRX BallIntakeMotorLeft{9};
  WPI_TalonSRX BallIntakeMotorRight{10};
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities



 public:

  Beak();
  void InitDefaultCommand() override;
  void GoBeak();
  void BeakIn();
  void BeakOut();
  int GetBeakPosition();

};
