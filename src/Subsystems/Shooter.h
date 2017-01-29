#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <CANTalon.h>

// ==========================================================================

class Shooter : public frc::Subsystem {
public:
	Shooter();

	void InitDefaultCommand();

	void shootFront();
	void shootBack();
	void stopFront();
	void stopBack();
	void feed();
	void deFeed();
	void stopFeed();
	void shootDefault(float right, float left);
	double getVelocity();

	CANTalon* leftFront;
	AnalogInput* feederSensor;

private:
	CANTalon* _leftRear;
	CANTalon* _rightFront;
	CANTalon* _rightRear;
	SpeedController* _feeder;
};

// ==========================================================================
