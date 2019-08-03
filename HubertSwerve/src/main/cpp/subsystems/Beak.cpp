/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Beak.h"
#include "commands/BeakCommand.h"
#include <OI.h>
#include <Robot.h>


Beak::Beak() : Subsystem("ExampleSubsystem") {

  BeakOpenSolenoid.Set(false);
  BeakExtendSolenoid.Set(false);
  
  BallIntakeSolenoid.Set(false);
  
    BallIntakeMotorRight.Follow(BallIntakeMotorLeft);
    BallIntakeMotorRight.SetInverted(false);
    BallIntakeMotorLeft.Set(0);
  
}

void Beak::InitDefaultCommand() {

  
  // Set the default command for a subsystem here.
  SetDefaultCommand(new BeakCommand());



} 

void Beak::GoBeak(){

  bool LB = OI::CoPilotJoystick.GetRawButton(5);
  bool RB = OI::CoPilotJoystick.GetRawButton(6);
  bool LT = OI::CoPilotJoystick.GetRawButton(7);
  bool RT = OI::CoPilotJoystick.GetRawButton(8);
  double YAxis = OI::CoPilotJoystick.GetAxis(frc::Joystick::AxisType::kYAxis);

    
    
    BeakOpenSolenoid.Set(LT);

     if (LB){
        BallIntakeSolenoid.Set(false);
        BeakExtendSolenoid.Set(true);
 
    }else if(RB) {
        BeakExtendSolenoid.Set(false);
    }
    
    if (RT) {
      BeakExtendSolenoid.Set(false);
      BallIntakeSolenoid.Set(true);
    }
    else
    {
      BallIntakeSolenoid.Set(false);
    }
    
    BallIntakeMotorLeft.Set(YAxis/2);
  
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
