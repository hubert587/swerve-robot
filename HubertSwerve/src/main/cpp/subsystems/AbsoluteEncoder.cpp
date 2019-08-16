

#include "subsystems/AbsoluteEncoder.h"
#include <cmath>

//class AbsoluteEncoder extends AnalogInput {

//double angleOffset;
//bool flipped = false;

AbsoluteEncoder::AbsoluteEncoder(int channel, double angleOffset):AnalogInput(channel) {
    flipped = false;
    angleOffset = (angleOffset*M_PI/180.0);

    //this.angleOffset = Math.toRadians(angleOffset);
}

AbsoluteEncoder::AbsoluteEncoder(int channel, double angleOffset, bool flipped):AnalogInput(channel) {

    angleOffset = (angleOffset*M_PI/180.0);
    flipped = flipped;
}

double AbsoluteEncoder::getAngle() {
    double angle;
    if (flipped) angle = (4.8 - GetVoltage()) * (2.0*M_PI) / 4.6;
    else angle = (GetVoltage() - 0.2) * (2.0*M_PI) / 4.6;
    return std::fmod((angle + angleOffset),(2.0*M_PI));
}

double AbsoluteEncoder::pidGet() {
    return getAngle();
}

