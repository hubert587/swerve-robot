
#include "subsystems/SwerveModule.h"
#include "RobotMap.h"
#include <cmath>
#include <iostream>

SwerveModule::SwerveModule(
            rev::CANSparkMax *driveCntr, 
            WPI_TalonSRX *steerCntr, 
            AbsoluteEncoder *steerEncdr, 
            double posX, 
            double posY) 
    {
    double RampValue = 0.0; // 0.5
    double BrakeValue = 1;
        enabled = false;
        steerController = steerCntr;
    	driveController = driveCntr;
    	steerEncoder = steerEncdr;
    	positionX = posX;
    	positionY = posY;
    	steerPID = new frc::PIDController(
            SWERVE_STEER_P, 
            SWERVE_STEER_I, 
            SWERVE_STEER_D,
    	    steerEncoder, 
            steerController);
    	steerPID->SetInputRange(0, 2.0*M_PI);
    	steerPID->SetOutputRange(-SWERVE_STEER_CAP, SWERVE_STEER_CAP);
    	steerPID->SetContinuous();
    	steerPID->Disable();

    driveController->SetSmartCurrentLimit(50);
    driveController->SetSecondaryCurrentLimit(80);
    driveController->SetOpenLoopRampRate(RampValue);
    driveController->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    driveController->BurnFlash();
}

void SwerveModule::enable() {
    steerPID->Enable();
    enabled = true;
}

void SwerveModule::disable() {
    steerPID->Disable();
    driveController->Set(0);
    steerController->Set(0);
    enabled = false;
}

void SwerveModule::set(double angle, double speed) {
    if (!enabled) return;
    double currentangle = steerEncoder->getAngle();
    //std:: cout << "currentangle = " << currentangle << " angle = " << angle;
    angle = wrapAngle(angle);
    double dist = fabs(angle-currentangle);
    if (dist > M_PI/2.0 && dist < 3.0*M_PI/2.0) {
        angle = wrapAngle(angle + M_PI);
        speed *= -1; 
    }
    // std:: cout << "dist = " << dist << " newangle = " << angle << "\n";
    steerPID->SetSetpoint(angle);
	driveController->Set(fmax(-1, fmin(1, speed)));
    //driveController->Set(0);

}

void SwerveModule::rest() {
    driveController->Set(0);
}

double SwerveModule::wrapAngle(double angle) {
    angle = fmod(angle, 2.0*M_PI);
    if (angle<0) angle += 2.0 *M_PI;
    return angle;
}

double SwerveModule::getPositionX() {
    return positionX;
}

double SwerveModule::getPositionY() {
    return positionY;
}

void SwerveModule::initDefaultCommand() {

}

AbsoluteEncoder* SwerveModule::GetAbsoluteEncoder() {
    return steerEncoder;
}