#include "subsystems/SwerveVector.h"
#include <cmath>

SwerveVector::SwerveVector (double X, double Y) {
    x = X;
    y = Y;
}

SwerveVector::SwerveVector () {
    x = 0.0;
    y = 0.0;
}

double SwerveVector::getAngle() {
    return atan2(y, x);
}

double SwerveVector::getMagnitude() {
    return hypot(x, y);
}

void SwerveVector::scale(double scalar) {
    x *= scalar;
    y *= scalar;
}

void SwerveVector::add(SwerveVector v) {
    x += v.x;
    y += v.y;
}

void SwerveVector::subtract(SwerveVector v) {
    x -= v.x;
    y -= v.y;
}

void SwerveVector::makePerpendicular() {
    double temp = x;
    x = y;
    y = -temp;
}