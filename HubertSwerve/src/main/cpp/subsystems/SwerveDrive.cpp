










//disclaimer, I have no idea what im doing


SwerveDrive::SwerveDirve() {
		//initialize array of modules
		//array can be any size, as long as the position of each module is specified in its constructor
		modules = new SwerveModule[] {
			//front left
			new SwerveModule(new Talon(RobotMap.FL_DRIVE),
					new Talon(RobotMap.FL_STEER),
					new AbsoluteEncoder(RobotMap.FL_ENCODER, Constants.FL_ENC_OFFSET),
					-Constants.WHEEL_BASE_WIDTH/2,
					Constants.WHEEL_BASE_LENGTH/2
					),
			//front right
			new SwerveModule(new Talon(RobotMap.FR_DRIVE), 
					new Talon(RobotMap.FR_STEER),
					new AbsoluteEncoder(RobotMap.FR_ENCODER, Constants.FR_ENC_OFFSET),
					Constants.WHEEL_BASE_WIDTH/2,
					Constants.WHEEL_BASE_LENGTH/2
					),
			//back left
			new SwerveModule(new Talon(RobotMap.BL_DRIVE),
					new Talon(RobotMap.BL_STEER),
					new AbsoluteEncoder(RobotMap.BL_ENCODER, Constants.BL_ENC_OFFSET),
					-Constants.WHEEL_BASE_WIDTH/2,
					-Constants.WHEEL_BASE_LENGTH/2
					),
			//back right
			new SwerveModule(new Talon(RobotMap.BR_DRIVE), 
					new Talon(RobotMap.BR_STEER),
					new AbsoluteEncoder(RobotMap.BR_ENCODER, Constants.BR_ENC_OFFSET),
					Constants.WHEEL_BASE_WIDTH/2,
					-Constants.WHEEL_BASE_LENGTH/2
					)
		};
	}




     void SwerveDrive::setPivot(double pivotX, double pivotY) {
		this.pivotX = pivotX;
		this.pivotY = pivotY;
	}

    void SwerveDrive::driveWithOrient(double translationX, double translationY, double rotation, double heading) {
		Vector[] vects = new Vector[modules.length];
		Vector transVect = new Vector(translationX, translationY),
				pivotVect = new Vector(pivotX, pivotY);
		
		//if there is only one module ignore rotation
		if (modules.length < 2)
			for (SwerveModule module : modules) 
				module.set(transVect.getAngle(), Math.min(1, transVect.getMagnitude())); //cap magnitude at 1

		double maxDist = 0;
		for (int i = 0; i < modules.length; i++) {
			vects[i] = new Vector(modules[i].positionX, modules[i].positionY);
			vects[i].subtract(pivotVect); //calculate module's position relative to pivot point
			maxDist = Math.max(maxDist, vects[i].getMagnitude()); //find farthest distance from pivot
		}
		
		double maxPower = 1;
		for (int i = 0; i < modules.length; i++) {
			//rotation motion created by driving each module perpendicular to
			//the vector from the pivot point
			vects[i].makePerpendicular();
			//scale by relative rate and normalize to the farthest module
			//i.e. the farthest module drives with power equal to 'rotation' variable
			vects[i].scale(rotation / maxDist);
			vects[i].add(transVect);
			//calculate largest power assigned to modules
			//if any exceed 100%, all must be scale down
			maxPower = Math.max(maxPower, vects[i].getMagnitude());
		}
		
		double power;
		for (int i = 0; i < modules.length; i++) {
			power = vects[i].getMagnitude() / maxPower; //scale down by the largest power that exceeds 100%
			if (power > .05) {
				modules[i].set(vects[i].getAngle()-Math.PI/2, power);
			} else {
				modules[i].rest();
			}
		}
	}


    void SwerveDrive::driveNormal(double translationX, double translationY, double rotation) {
		driveWithOrient(translationX, translationY, rotation, 0);
	}

    void SwerveDrive::enable() {
		for (SwerveModule module : modules) module.enable();
	}
	
	void SwerveDrive::disable() {
		for (SwerveModule module : modules) module.disable();
	}

    void SwerveDrive::initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
