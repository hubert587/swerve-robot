
#pragma once

//#include "frc/SpeedController.h"
//#include "frc/PIDController.h"
//#include <ctre/Phoenix.h>
//#include <OI.h>

#include <ctre/Phoenix.h>
#include <OI.h>
#include <frc/AnalogInput.h>

class AbsoluteEncoder : public frc::AnalogInput {

	double angleOffset;
	bool flipped = false;
	

 public:
	AbsoluteEncoder(int channel, double angleOffset);
	
	AbsoluteEncoder(int channel, double angleOffset, bool flipped);
	
     double getAngle();
	
	 double pidGet();
};