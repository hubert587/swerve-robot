Vector::Vector (double x, double y) {
    this.x = x;
    this.y = y;
}

double Vector::getAngle() {
    return Math.atan2(y, x);
}

double Vector::getMagnitude() {
    return Math.hypot(x, y);
}

void Vector::scale(double scalar) {
    x *= scalar;
    y *= scalar;
}

void Vector::add(Vector v) {
    x += v.x;
    y += v.y;
}

void Vector::subtract(Vector v) {
    x -= v.x;
    y -= v.y;
}

void Vector::makePerpendicular() {
    double temp = x;
    x = y;
    y = -temp;
}