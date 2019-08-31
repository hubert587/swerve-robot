/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveCommand.h"
#include "Robot.h"
#include <cmath>

DriveCommand::DriveCommand() {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_drivetrain);
  gear0 = 0;
  iAMnotU = true;
}

// Called just before this Command runs the first time
void DriveCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveCommand::Execute() {

bool LB = OI::PilotJoystick.GetRawButtonPressed(5);
bool RB = OI::PilotJoystick.GetRawButtonPressed(6);
bool Y = OI::PilotJoystick.GetRawButtonPressed(4);
bool A = OI::PilotJoystick.GetRawButtonPressed(2);
if (LB) gear0 = 0;
if (RB) gear0 = 1;
double speedDiv = 1.0;
double angel = 0.0;
if (gear0 == 1) speedDiv = 2.0;

if (Y == true) {
  iAMnotU = true;
  m_imu.Reset();
}

if (A == true) {
  iAMnotU = false;
}

if (iAMnotU == true) angel = ((m_imu.GetAngle() * M_PI) / 180.0);

//Robot::m_drivetrain.Drive();
Robot::m_drivetrain.driveWithOrient
                               (-Robot::m_oi.PilotJoystick.GetX() / speedDiv,
                                 Robot::m_oi.PilotJoystick.GetY() / speedDiv,
                                -Robot::m_oi.PilotJoystick.GetZ() / speedDiv, angel);

}



// Make this return true when this Command no longer needs to run execute()
bool DriveCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveCommand::Interrupted() {}
