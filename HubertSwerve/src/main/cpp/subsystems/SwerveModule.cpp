


#include "subsystems/SwerveModule.h"

SwerveModule::SwerveModule(
    SpeedController driveController, 
    SpeedController steerController, 
    AbsoluteEncoder steerEncoder, 
    double positionX, 
    double positionY) 
    {
        this.steerController = steerController;
    	this.driveController = driveController;
    	this.steerEncoder = steerEncoder;
    	this.positionX = positionX;
    	this.positionY = positionY;
    	steerPID = new PIDController(
            Constants.SWERVE_STEER_P, 
            Constants.SWERVE_STEER_I, 
            Constants.SWERVE_STEER_D,
    	    steerEncoder, 
            steerController);
    	steerPID.setInputRange(0, 2*Math.PI);
    	steerPID.setOutputRange(-Constants.SWERVE_STEER_CAP, Constants.SWERVE_STEER_CAP);
    	steerPID.setContinuous();
    	steerPID.disable();
}

void SwerveModule::enable() {
    steerPID.enable();
    enabled = true;
}

void SwerveModule::disable() {
    steerPID.disable();
    driveController.set(0);
    steerController.set(0);
    enabled = false;
}

void SwerveModule::set(double angle, double speed) {
    if (!enabled) return;
    angle = wrapAngle(angle);
    double dist = Math.abs(angle-steerEncoder.getAngle());
    if (dist > Math.PI/2 && dist < 3*Math.PI/2) {
        angle = wrapAngle(angle + Math.PI);
        speed *= -1; 
    }
    steerPID.setSetpoint(angle);
	driveController.set(Math.max(-1, Math.min(1, speed)));
}

void SwerveModule::rest() {
    driveController.set(0);
}

double SwerveModule::wrapAngle(double angle) {
    angle %= 2*Math.PI;
    if (angle<0) angle += 2*Math.PI;
    return angle;
}

void SwerveModule::initDefaultCommand() {

}