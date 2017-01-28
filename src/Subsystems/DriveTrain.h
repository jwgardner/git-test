#pragma once

#include <Commands/Subsystem.h>
#include "Modules/AnalogChannelVolt.h"
#include "Subsystems/GyroSub.h"

class DriveTrain : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	static constexpr double pi = 3.14159265358979323846264;

	bool unwinding;

	// Steering Variables
	double radian; // input steering angle in radians
	double A;      // A is the ratio of X to turn harder
	double W; // W is the distance form the mid-point of one back wheel to the
			  // mid-point of the other back wheel
	double X; // X is the distance form the mid-point of the back wheels to the
			  // mid-point of the front wheels
	double Y; // Y is the distance from the mid-point of one front wheel to the
			  // mid-point of the other front wheel

	double FL; // FL, distance from Front Left Wheel to the center of rotation
	double FR; // FR, distance from Front Right Wheel to the center of rotation
	double RL; // RL, distance from Rear Left Wheel to the center of rotation
	double RR; // RR, distance from Rear Right Wheel to the center of rotation

	double Z; // Z, distance form A * X to center of rotation

	double thetaRC; // Angle used to calculate all other angles

	double thetaFL; // thetaFL, angle from Front Left Wheel to the center of rotation
	double thetaFR; // thetaFR, angle from Front Right Wheel to the center of rotation
	double thetaRL; // thetaRL, angle from Rear Left Wheel to the center of rotation
	double thetaRR; // thetaRR, angle from Rear Right Wheel to the center of rotation
	double FRRatio; // Ratio of Speed of Front Right wheel
	double FLRatio; // Ratio of Speed of Front Left wheel
	double RRRatio; // Ratio of Speed of Rear Right wheel
	double RLRatio; // Ratio of Speed of Rear Left wheel

	double FLOffset; // Front left wheel position
	double FROffset; // Front right wheel position
	double RLOffset; // Rear left wheel position
	double RROffset; // Rear right wheel position

	// Crab & Pivot Variables
	double position; // Input position for crab
	double AP;       // variable used in swerve calculations
	double BP;       // variable used in swerve calculations
	double CP;       // variable used in swerve calculations
	double DP;       // variable used in swerve calculations

	// Inversion Variables
	int FLInv; // Direction of front left drive motor
	int FRInv; // Direction of front right drive motor
	int RLInv; // Direction of right left drive motor
	int RRInv; // Direction of right rear drive motor

	// Pivot Variables
	double radius;            // distance from center to each wheel
	double velocity;          // robot speed
	double angularvelocity;   // input from OI
	double robotangle;        // current robot angle from Gyro
	double inverserobotangle; // 2pi-robotangle

	// Wheel position in angle relative to robot
	double FLWP;
	double FRWP;
	double RLWP;
	double RRWP;

	// Wheel velocities in X direction
	double FLXVel;
	double FRXVel;
	double RLXVel;
	double RRXVel;

	// Wheel velocities in Y direction
	double FLYVel;
	double FRYVel;
	double RLYVel;
	double RRYVel;

	double FLPos;
	double FRPos;
	double RRPos;
	double RLPos;

	// Wheel velocities
	double FLVel;
	double FRVel;
	double RLVel;
	double RRVel;

	// Wheel angle differences from robot angle
	double deltaFL;
	double deltaFR;
	double deltaRL;
	double deltaRR;

	double CorrectSteerSetpoint(double setpoint);
	void SetSteerSetpoint(float FLSetPoint, float FRSetPoint, float RLSetPoint, float RRSetPoint);
	void SetDriveSpeed(float FLSpeed, float FRSpeed, float RLSpeed, float RRSpeed);
	void CurrentLimit();

	float FLSOTimer;
	float FRSOTimer;
	float RLSOTimer;
	float RRSOTimer;

	float lastx;
	float lasty;
	float lasttwist;

	bool DriveBackFlag;

	double FLValue; // Current value measured from front left drive encoder
	double FRValue; // Current value measured from front right drive encoder
	double RLValue; // Current value measured from rear left drive encoder
	double RRValue; // Current value measured from rear right drive encoder

public:
	PIDController *frontLeft; // PID object for front left steering motor
	CANTalon *frontLeftDrive; // Speed controller for front left drive motor
	AnalogChannelVolt *frontLeftPos; // Encoder for front left steering motor
	CANTalon *frontLeftSteer; // Speed controller for front left steering motor

	PIDController *frontRight;        // PID object for front right steering motor
	CANTalon *frontRightDrive;        // Speed controller for front right drive motor
	AnalogChannelVolt *frontRightPos; // Encoder for front right steering motor
	CANTalon *frontRightSteer;        // Speed controller for front right steering motor

	PIDController *rearLeft;        // PID object for rear left steering motor
	CANTalon *rearLeftDrive;        // Speed controller for rear left drive motor
	AnalogChannelVolt *rearLeftPos; // Encoder for rear left steering motor
	CANTalon *rearLeftSteer;        // Speed controller for rear left steering motor

	PIDController *rearRight; // PID object for rear right steering motor
	CANTalon *rearRightDrive; // Speed controller for rear right drive motor
	AnalogChannelVolt *rearRightPos; // Encoder for rear right steering motor
	CANTalon *rearRightSteer; // Speed controller for rear right steering motor

	DriveTrain();
	void SetWheelbase(float w, float x, float y); // sets dimensions of drive train
	void SetMaxSpeed(float MaxSpeed); // sets the max speed of drive motors
	void SetOffsets(double FLOff, double FROff, double RLOff, double RROff); // sets wheels to correct positions
	void InitDefaultCommand(); // sets default command
	void Crab(float twist, float y, float x, bool operatorControl); // default driving command
	// bool ResetTurns();
	void Lock();
	void SideLock(); // locks steering
	bool GetDriveBackFlag();
	void SetDriveBackFlag(bool flag);
	bool unwind();     // float y, float x); //unwinds all wheels
	void doneunwind(); // called when unwinding is finished
	// bool unwindwheel(AnalogChannelVolt*, PIDController*, double offset, bool output); //unwinds one wheel to fix wires (returns false if not done unwinding)
	void GyroCrab(float desiredangle, float y, float x, bool operatorControl); // drive using gyro values
	void FieldCentricCrab(float twist, float y, float x, bool operatorControl); // drive at 90 degree angle to field
	void PositionModeTwist(float desiredangle);
	void updateDistanceEncoders(); // updates the values of drive train variables with distance encoder values
	double getDistanceEncodersValues(); // returns average value from driving encoders
	void zeroDistanceEncoders(); // Reset driving encoders to 0
	void zeroSteeringEncoders(); // Reset steering encoders to 0
	void setWheelOffsets();
	void loadWheelOffsets();
	void LogSettings(double fl, double fr, double rl, double rr);
	void Dashboard();
	void CrabInit();
	void SetWheelsStraight();
	void ArcadeDriveMode(float y, float x);
	void disableSpeedControl();
	void enableSpeedControl();
	void enablePositionControl();
	void enableSteeringPID();
};
