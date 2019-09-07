
#pragma once

#include "frc/SpeedController.h"
#include "frc/PIDController.h"
#include "AbsoluteEncoder.h"
#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
//#include <OI.h>


class SwerveModule {

    private:
    
        frc::PIDController *steerPID;
        WPI_TalonSRX       *steerController; 
        rev::CANSparkMax   *driveController; //SpeedController used so this can be talon, victor, jaguar, CAN talon...
        AbsoluteEncoder   *steerEncoder;
        double positionX, positionY; //position of this wheel relative to the center of the robot
        bool enabled;

    public:
        SwerveModule(
            rev::CANSparkMax *driveCntr, 
            WPI_TalonSRX *steerCntr, 
            AbsoluteEncoder *steerEncdr, 
            double posX, 
            double posY);
    
        void enable();
        void disable();
        void set(double angle, double speed);
        void rest();
        double wrapAngle(double angle);
        double getPositionX();
        double getPositionY();
        void initDefaultCommand();

        AbsoluteEncoder* GetAbsoluteEncoder();
};
