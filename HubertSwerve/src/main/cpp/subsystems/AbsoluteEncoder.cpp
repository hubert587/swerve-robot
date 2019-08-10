

#include "subsystems/AbsoluteEncoder.h"

//class AbsoluteEncoder extends AnalogInput {

double angleOffset;
boolean flipped = false;

AbsoluteEncoder::AbsoluteEncoder(int channel, double angleOffset) {
    super(channel);
    this.angleOffset = Math.toRadians(angleOffset);
}

AbsoluteEncoder::AbsoluteEncoder(int channel, double angleOffset, boolean flipped) {
    super(channel);
    this.angleOffset = Math.toRadians(angleOffset);
    this.flipped = flipped;
}

double AbsoluteEncoder::getAngle() {
    double angle;
    if (flipped) angle = (4.8 - getVoltage()) * (2*Math.PI) / 4.6;
    else angle = (getVoltage() - 0.2) * (2*Math.PI) / 4.6;
    return (angle + angleOffset) % (2*Math.PI);
}

double AbsoluteEncoder::pidGet() {
    return getAngle();
}

