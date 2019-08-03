/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LiftCommand.h"
#include <subsystems/Lift.h>
#include <Robot.h>

LiftCommand::LiftCommand() {
  
  // Use Requires() here to declare subsystem dependencies
   Requires(&Robot::m_lift);
  
  //LiftPosition = position;


}

// Called just before this Command runs the first time
void LiftCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LiftCommand::Execute() {

  int CurrentPosition = Robot::m_lift.GetCurrentPosition();

  Robot::m_lift.Control();
  /*
  if(CurrentPosition == LiftPosition){  }

  else if(CurrentPosition < LiftPosition){

    Robot::m_lift.LiftUp(LiftPosition);

  } else if(CurrentPosition > LiftPosition){

    Robot::m_lift.LiftDown(LiftPosition);

  } 
  */

}

// Make this return true when this Command no longer needs to run execute()
bool LiftCommand::IsFinished() { 

  if(LiftPosition == Robot::m_lift.GetCurrentPosition()){

    return true;

  } else if(LiftPosition == 0){
    
    Robot::m_lift.LiftStop();
    
    } else {

   return false;
  
    }

  }

// Called once after isFinished returns true
void LiftCommand::End() {

  Robot::m_lift.LiftStop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftCommand::Interrupted() {

  Robot::m_lift.LiftStop();

}
