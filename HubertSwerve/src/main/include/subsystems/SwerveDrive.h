#pragma once

#include <frc/commands/Subsystem.h>
#include "SwerveModule.h"
#include "RobotMap.h"

class SwerveDrive : public frc::Subsystem {


    private:
        double pivotX, pivotY;
	    SwerveModule *modules[NUMBER_SWERVE_MODULES];
    
    public:
        SwerveDrive();
        void setPivot(double pivotX, double pivotY);
        void driveWithOrient(double translationX, double translationY, double rotation, double heading);
        void driveNormal(double translationX, double translationY, double rotation);
        void enable();
        void disable();
        void InitDefaultCommand() override;
};