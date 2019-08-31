#pragma once


class SwerveVector {

    public:
        SwerveVector();
        SwerveVector (double x, double y);
        double getAngle();
        double getMagnitude();
        void scale(double scalar);
        void add(SwerveVector v);
        void subtract(SwerveVector v);
        void makePerpendicular();
        void rotate(double radians);

    private:
        double x;
        double y;
};