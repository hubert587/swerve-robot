/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <commands/LiftCommand.h>
#include <frc/WPILib.h>

frc::Joystick OI::PilotJoystick{0};
frc::Joystick OI::CoPilotJoystick{1};

OI::OI() {
  
  // Process operator interface input here.

  /*
  A.WhenPressed(new LiftCommand{1});
  B.WhenPressed(new LiftCommand{2});
  Y.WhenPressed(new LiftCommand{3});
  X.WhenPressed(new LiftCommand{0});
  */



}
