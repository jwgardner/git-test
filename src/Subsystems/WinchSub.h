#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <CANTalon.h>

// ==========================================================================

class WinchSub : public frc::Subsystem {
public:
	WinchSub();

	void InitDefaultCommand();

	bool ShooterIsRaised() const;

	// TODO - Fix casing of method names
	void setPos(double pos);
	void readPos();
	void disablePositionControl();
	void reset();
	void climb();
	void climbReverse();
	void stopClimb();

	PIDController* shooter; // TODO - Make this private
	const static bool angleSensor; // TODO - Make this private

private:
	CANTalon* _motor;
	AnalogInput* _shooterSensor;
	bool _shooterRaised;
};

// ==========================================================================
