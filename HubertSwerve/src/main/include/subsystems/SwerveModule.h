
#pragma once

#include "frc/SpeedController.h"
#include "frc/PIDController.h"
//#include <ctre/Phoenix.h>
//#include <OI.h>


class SwerveModule {

    private:
    
        PIDController steerPID;
        SpeedController steerController, driveController; //SpeedController used so this can be talon, victor, jaguar, CAN talon...
        public AbsoluteEncoder steerEncoder;
        double positionX, positionY; //position of this wheel relative to the center of the robot
        boolean enabled = false;

    public:
        ServeModule(
            SpeedController driveController, 
            SpeedController steerController, 
            AbsoluteEncoder steerEncoder, 
            double positionX, 
            double positionY);
    
        void enable();
        void disable();
        void set(double angle, double speed);
        void rest();
        double wrapAngle(double angle);
        void SwerveModule::initDefaultCommand();
};
