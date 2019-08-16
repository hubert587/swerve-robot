/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */


//SM means Steering Motor
enum SM_Constant{
SM_LeftFront = 5,
SM_LeftBack = 8,
SM_RightFront = 6,
SM_RightBack = 7,
};

//DM means Drive Motor
enum DM_Constant{
DM_LeftFront = 3,
DM_LeftBack = 1,
DM_RightFront = 4,
DM_RightBack = 2,
};

//SE means Steering Encoder
enum SE_Constant{
SE_LeftFront = 3,
SE_LeftBack = 2,
SE_RightFront = 1,
SE_RightBack = 0,
};

//SEO means Steering Encoder Offset
enum SEO_Constant{
SEO_LeftFront = 0,
SEO_LeftBack = 0,
SEO_RightFront = 0,
SEO_RightBack = 0,
//All SEO is currently set to 0 because we still need to figure out the values
};


enum SwerveModule_Constant{
SwerveModule_LeftFront = 0,
SwerveModule_LeftBack = 1,
SwerveModule_RightFront = 2,
SwerveModule_RightBack = 3,
NUMBER_SWERVE_MODULES = 4
};

const double WHEEL_BASE_WIDTH = 24.0;
const double WHEEL_BASE_LENGTH = 24.0;

const double SWERVE_STEER_P = .5;
const double SWERVE_STEER_I = 0;
const double SWERVE_STEER_D = 0;
const double SWERVE_STEER_CAP = .5; //speed limit on the steering motor