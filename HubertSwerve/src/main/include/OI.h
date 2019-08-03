/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>

class OI {
 public:

static frc::Joystick PilotJoystick;
static frc::Joystick CoPilotJoystick;

frc::JoystickButton A{&CoPilotJoystick, 2};
frc::JoystickButton B{&CoPilotJoystick, 3};
frc::JoystickButton X{&CoPilotJoystick, 1};
frc::JoystickButton Y{&CoPilotJoystick, 4};

  OI();
};
