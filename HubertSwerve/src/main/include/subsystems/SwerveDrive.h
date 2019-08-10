


















class SwerveDrive : public frc::Subsystem {


    private:
        double pivotX, pivotY;
	    SwerveModule[] modules;
    
    public:
        SwerveDirve();
        void setPivot(double pivotX, double pivotY);
        void driveWithOrient(double translationX, double translationY, double rotation, double heading);
        void driveNormal(double translationX, double translationY, double rotation);
        void enable();
        void disable();
        void initDefaultCommand(); 
}