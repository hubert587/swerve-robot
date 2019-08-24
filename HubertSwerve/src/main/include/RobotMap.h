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
SM_LeftBack = 6,
SM_RightFront = 8,
SM_RightBack = 7,
};

//DM means Drive Motor
enum DM_Constant{
DM_LeftFront = 4,
DM_LeftBack = 3,
DM_RightFront = 1,
DM_RightBack = 2,
};

//SE means Steering Encoder
enum SE_Constant{
SE_LeftFront = 0,
SE_LeftBack = 1,
SE_RightFront = 2,
SE_RightBack = 3,
};

//SEO means Steering Encoder Offset
const double SEO_LeftFront = 2.69 + 0.85; 
const double SEO_LeftBack = 0.075 - 0.2; //2.595;
const double SEO_RightFront = 2.979 + 0.35; //4.651;
const double SEO_RightBack = 0.715 + 1.7;
//All SEO is currently set to 0 because we still need to figure out the values


enum SwerveModule_Constant{
SwerveModule_LeftFront = 0,
SwerveModule_LeftBack = 1,
SwerveModule_RightFront = 2,
SwerveModule_RightBack = 3,
NUMBER_SWERVE_MODULES = 4
};

const double WHEEL_BASE_WIDTH = 24.0;
const double WHEEL_BASE_LENGTH = 22.0;

const double SWERVE_STEER_P = .5;
const double SWERVE_STEER_I = 0;
const double SWERVE_STEER_D = 0;
const double SWERVE_STEER_CAP = .7; //speed limit on the steering motor