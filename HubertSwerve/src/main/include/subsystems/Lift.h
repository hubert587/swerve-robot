/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <OI.h>


class Lift : public frc::Subsystem {
 private:

  int CurrentPosition;

  WPI_TalonSRX LiftMotorLeft{11};
  WPI_TalonSRX LiftMotorRight{12};

   WPI_TalonSRX LVL3Motor{13};

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  



 public:
  Lift();
  void InitDefaultCommand() override;
  void Control();

  void LiftUp(int Position);
  void LiftDown(int Position);
  void LiftStop();
  int GetCurrentPosition();

};
