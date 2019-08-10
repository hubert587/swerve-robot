/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "commands/DriveCommand.h"
#include <frc/Joystick.h>
#include <OI.h>
#include <Robot.h>
#include <iostream>
#include <rev/CANSparkMax.h>

bool Drivetrain::driveModeDifferential = true;

Drivetrain::Drivetrain() : Subsystem("DriveTrain") {     
    std::cout << "Set up Drivetrain\n";
    double RampValue = 0.0; // 0.5
    double BrakeValue = 1;
    /*FrontLeftMotor.SetRampRate(RampValue);
    FrontRightMotor.SetRampRate(RampValue);
    RearLeftMotor.SetRampRate(RampValue);
    RearRightMotor.SetRampRate(RampValue);*/
    FrontLeftMotor.SetSmartCurrentLimit(50);
    FrontRightMotor.SetSmartCurrentLimit(50);
    RearLeftMotor.SetSmartCurrentLimit(50);
    RearRightMotor.SetSmartCurrentLimit(50);
    FrontLeftMotor.SetSecondaryCurrentLimit(80);
    FrontRightMotor.SetSecondaryCurrentLimit(80);
    RearLeftMotor.SetSecondaryCurrentLimit(80);
    RearRightMotor.SetSecondaryCurrentLimit(80);
    FrontLeftMotor.SetOpenLoopRampRate(RampValue);
    FrontRightMotor.SetOpenLoopRampRate(RampValue);
    RearLeftMotor.SetOpenLoopRampRate(RampValue);
    RearRightMotor.SetOpenLoopRampRate(RampValue);


    FrontLeftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    FrontRightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    RearLeftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    RearRightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    DrivetrainSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    RampExtendSolenoid.Set(false);

    RearLeftMotor.BurnFlash();
    RearRightMotor.BurnFlash();
    FrontLeftMotor.BurnFlash();
    FrontRightMotor.BurnFlash();

}

void Drivetrain::InitDefaultCommand() {

SetDefaultCommand(new DriveCommand{});

}

void Drivetrain::Drive(){

double YAxis = OI::PilotJoystick.GetAxis(frc::Joystick::AxisType::kYAxis);
double XAxis = OI::PilotJoystick.GetAxis(frc::Joystick::AxisType::kXAxis);
double ZAxis = OI::PilotJoystick.GetAxis(frc::Joystick::AxisType::kZAxis);
double ZRAxis = OI::PilotJoystick.GetAxis(frc::Joystick::AxisType::kThrottleAxis);
bool LB = OI::PilotJoystick.GetRawButtonPressed(5);
bool RB = OI::PilotJoystick.GetRawButtonPressed(6);
//bool Trigger = OI::PilotJoystick.GetRawButton(7);
//bool TriggerPressed = OI::PilotJoystick.GetRawButtonPressed(7);
bool Trigger2 = OI::PilotJoystick.GetRawButton(8);


double JoystickY_1 = -YAxis;
double JoystickX_1 = -XAxis;
double JoystickZ_1 = ZAxis *0.9;
double JoystickThrottle_1 = -ZRAxis;

if(OI::PilotJoystick.GetRawButtonPressed(10))
      RampExtendSolenoid.Set(true);
if(OI::PilotJoystick.GetRawButtonPressed(9))
      RampExtendSolenoid.Set(false);

//if (TriggerPressed)m_imu.Reset();

/*if(Trigger == 1){

JoystickY_1 = -YAxis/4;
JoystickX_1 = -XAxis/4;
JoystickZ_1 = ZAxis/4;
JoystickThrottle_1 = -ZRAxis/4;

}*/
if(Trigger2 == 1){

JoystickY_1 = -YAxis/2;
JoystickX_1 = -XAxis/2;
JoystickZ_1 = ZAxis/2;
JoystickThrottle_1 = -ZRAxis/2;

}



if(LB == true){

driveModeDifferential = false;
DrivetrainSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
//RearLeftMotor.Follow(rev::CANSparkMax::kFollowerDisabled, 1);
//RearRightMotor.Follow(rev::CANSparkMax::kFollowerDisabled, 3);
std::cout << "Switch to Mecanum\n";

  
//if(RearLeftMotor.IsFollower()){

//    std::cout << "Is Following\n";

//}

/*if(RearRightMotor.IsFollower()){

    std::cout << "Is Following\n";

}*/

}

else if(RB == true){

driveModeDifferential = true;
DrivetrainSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
/*RearLeftMotor.Follow(FrontLeftMotor);
RearRightMotor.Follow(FrontRightMotor);*/
std::cout << "Switch to Tank\n";

/*if(RearLeftMotor.IsFollower()){

    std::cout << "Is Following\n";

}

if(RearRightMotor.IsFollower()){

    std::cout << "Is Following\n";

}*/

}

if(driveModeDifferential){


   // TankTimeRear.TankDrive( JoystickThrottle_1, JoystickY_1);
   // TankTimeFront.TankDrive( JoystickThrottle_1, JoystickY_1);
    TankTimeRear.ArcadeDrive(-JoystickY_1, -JoystickZ_1);
    TankTimeFront.ArcadeDrive(-JoystickY_1, -JoystickZ_1);
    MecanumTime.FeedWatchdog();
    std::cout << "Run to Tank\n";
printf("tersbbbb");

} else{

   /* double ang = m_imu.GetAngle();
    static int PrintTime = 0;
    PrintTime++; if (PrintTime > 300){
    std::cout << "ang = " << ang << "\n";
    PrintTime = 0;
    } */

    //double ang = 0;
    //if (Trigger)
        //ang = m_imu.GetAngle();

    MecanumTime.DriveCartesian(-JoystickX_1, -JoystickY_1, -JoystickZ_1, 0);
    TankTimeRear.FeedWatchdog();
    TankTimeFront.FeedWatchdog();

   std::cout << "Run to Mecanum\n";
   printf("terst");

}





}


// Put methods for controlling this subsystem
// here. Call these from Commands.
