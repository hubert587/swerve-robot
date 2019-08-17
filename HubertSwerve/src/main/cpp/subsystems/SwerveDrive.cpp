
#include "commands/DriveCommand.h"
#include "RobotMap.h"
#include "subsystems/SwerveModule.h"
#include "subsystems/SwerveVector.h"
#include "subsystems/SwerveDrive.h"


//disclaimer, I have no idea what im doing


SwerveDrive::SwerveDrive() : Subsystem("swervedrive") {
	printf("testing");
		//initialize array of modules
			//front left
			modules[SwerveModule_LeftFront] = new SwerveModule(
				    new rev::CANSparkMax(DM_LeftFront, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
				    new WPI_TalonSRX(SM_LeftFront),
					new AbsoluteEncoder(SE_LeftFront, SEO_LeftFront),
					(-WHEEL_BASE_WIDTH/2.0),
					(WHEEL_BASE_LENGTH/2.0)
					);
			//front right
			modules[SwerveModule_RightFront] = new SwerveModule(				    
				    new rev::CANSparkMax(DM_RightFront, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
				    new WPI_TalonSRX(SM_RightFront),
					new AbsoluteEncoder(SE_RightFront, SEO_RightFront),
					(WHEEL_BASE_WIDTH/2.0),
					(WHEEL_BASE_LENGTH/2.0)
					);
			//back left
			modules[SwerveModule_LeftBack] = new SwerveModule(				    
				    new rev::CANSparkMax(DM_LeftBack, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
				    new WPI_TalonSRX(SM_LeftBack),
					new AbsoluteEncoder(SE_LeftBack, SEO_LeftBack),
					(-WHEEL_BASE_WIDTH/2.0),
					(-WHEEL_BASE_LENGTH/2.0)
					);
			//back right
			modules[SwerveModule_RightBack] = new SwerveModule(				    
				    new rev::CANSparkMax(DM_RightBack, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
				    new WPI_TalonSRX(SM_RightBack),
					new AbsoluteEncoder(SE_RightBack, SEO_RightBack),
					(WHEEL_BASE_WIDTH/2.0),
					(-WHEEL_BASE_LENGTH/2.0)
					);
		pivotX = 0;
		pivotY = 0;
	}




     void SwerveDrive::setPivot(double _pivotX, double _pivotY) {
		pivotX = _pivotX;
		pivotY = _pivotY;
	}

    void SwerveDrive::driveWithOrient(double translationX, double translationY, double rotation, double heading) {
		SwerveVector vects[NUMBER_SWERVE_MODULES];
		SwerveVector transVect{translationX, translationY};
		SwerveVector pivotVect{pivotX, pivotY};
		
		//if there is only one module ignore rotation
		if (NUMBER_SWERVE_MODULES < 2)
			for (int i = 0; i < NUMBER_SWERVE_MODULES; i++) {
				modules[i]->set(transVect.getAngle(), fmin(1, transVect.getMagnitude())); //cap magnitude at 1
			}

		double maxDist = 0;
		for (int i = 0; i < NUMBER_SWERVE_MODULES; i++) {
			vects[i] = SwerveVector{modules[i]->getPositionX(), modules[i]->getPositionY()};
			vects[i].subtract(pivotVect); //calculate module's position relative to pivot point
			maxDist = fmax(maxDist, vects[i].getMagnitude()); //find farthest distance from pivot
		}
		
		double maxPower = 1;
		for (int i = 0; i < NUMBER_SWERVE_MODULES; i++) {
			//rotation motion created by driving each module perpendicular to
			//the vector from the pivot point
			vects[i].makePerpendicular();
			//scale by relative rate and normalize to the farthest module
			//i.e. the farthest module drives with power equal to 'rotation' variable
			vects[i].scale(rotation / maxDist);
			vects[i].add(transVect);
			//calculate largest power assigned to modules
			//if any exceed 100%, all must be scale down
			maxPower = fmax(maxPower, vects[i].getMagnitude());
		}
		
		double power;
		for (int i = 0; i < NUMBER_SWERVE_MODULES; i++) {
			power = vects[i].getMagnitude() / maxPower; //scale down by the largest power that exceeds 100%
			if (power > .05) {
				modules[i]->set(vects[i].getAngle()-(M_PI/2.0), power);
			} else {
				modules[i]->rest();
			}
		}
	}


    void SwerveDrive::driveNormal(double translationX, double translationY, double rotation) {
		driveWithOrient(translationX, translationY, rotation, 0);
	}

    void SwerveDrive::enable() {
		//to test module by module
		//modules[2]->enable();

		for (int i = 0; i < NUMBER_SWERVE_MODULES; i++) {
			modules[i]->enable();
		}
	}
	
	void SwerveDrive::disable() {
		for (int i = 0; i < NUMBER_SWERVE_MODULES; i++) {
			modules[i]->disable();
		}
	}

    void SwerveDrive::InitDefaultCommand() {
		SetDefaultCommand(new DriveCommand{});
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }