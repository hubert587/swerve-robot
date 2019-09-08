

#include "subsystems/AbsoluteEncoder.h"
#include <cmath>
#include <iostream>
#include <string>
#include <frc/smartdashboard/SmartDashboard.h>

//class AbsoluteEncoder extends AnalogInput {

//double angleOffset;
//bool flipped = false;

AbsoluteEncoder::AbsoluteEncoder(int channel, double angOffset):AnalogInput(channel) {
    flipped = false;
    //angleOffset = (angOffset*(2.0*M_PI)/4.6);
    angleOffset = angOffset;
    //this.angleOffset = Math.toRadians(angleOffset);
}

AbsoluteEncoder::AbsoluteEncoder(int channel, double angOffset, bool flip):AnalogInput(channel) {

    //angleOffset = (angOffset*(2.0*M_PI)/4.6);
    angleOffset = angOffset;
    flipped = flip;
}

double AbsoluteEncoder::getAngle() {
    double angle;
    double voltage = GetVoltage();
    if (voltage > 4.8) voltage = 4.8;
    if (voltage < 0.2) voltage = 0.2;
    //std::cout << GetChannel() << "v=" << voltage;
    if (GetChannel() == 3) std::cout <<"\n";
    if (flipped) angle = (4.8 - voltage) * (2.0*M_PI) / 4.6;
    else angle = (voltage - 0.2) * (2.0*M_PI) / 4.6;
    std::cout << GetChannel() << "a=" << angle << "o=" << angleOffset << " ";
    return std::fmod((angle + angleOffset),(2.0*M_PI));
}

double AbsoluteEncoder::PIDGet() {
    return getAngle();
}

double AbsoluteEncoder::GetAngleOffset() {
    return angleOffset;
}

void AbsoluteEncoder::SetAngleOffset(double offset) {
    angleOffset = offset;
}

