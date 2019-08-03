/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Lift.h"
#include "commands/LiftCommand.h"
#include <OI.h>


Lift::Lift() : Subsystem("Lift") {
  
  LVL3Motor.Set(0);

  LiftMotorRight.SetInverted(true);

  LiftMotorRight.Follow(LiftMotorLeft);

  LiftMotorLeft.Set(0);

  CurrentPosition = 1;

  LiftMotorLeft.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal_NormallyOpen);

  LiftMotorLeft.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal_NormallyOpen);
  
  



}

void Lift::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new LiftCommand());
  
}

void Lift::Control()  {

  double ZAxis = OI::CoPilotJoystick.GetAxis(frc::Joystick::AxisType::kThrottleAxis);
  if (ZAxis >= 0.1)
  {
     LiftMotorLeft.Set(-ZAxis/2);
  }
  else if (0.1 > ZAxis && ZAxis > -0.1)
  {

    LiftMotorLeft.Set(0.09);

  }
  else
  {
    LiftMotorLeft.Set(-ZAxis);
  }

 bool BK = OI::CoPilotJoystick.GetRawButton(9);
 bool FW = OI::CoPilotJoystick.GetRawButton(10);
 bool BX = OI::CoPilotJoystick.GetRawButton(1);
 if (BK == true)
 {
  LVL3Motor.Set(-0.75);
 }
 else if (FW == true)
 {
  LVL3Motor.Set(.5);
 }
else if (BX == true){   LVL3Motor.Set(0.75);
}


 else
 {
  LVL3Motor.Set(0);
 }

}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Lift::LiftUp(int Position){

//LiftMotorLeft.Set(0.5);

}

void Lift::LiftDown(int Position){

//LiftMotorRight.Set(-0.5);

}

void Lift::LiftStop(){

//LiftMotorLeft.Set(0);

}

int Lift::GetCurrentPosition(){

  return CurrentPosition;

}