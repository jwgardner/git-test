#include "Subsystems/Shooter.h"
#include <CANTalon.h>
#include "Commands/ShootDefault.h"
#include "RobotMap.h"

const int RPM = 7000;

// ==========================================================================

Shooter::Shooter()
: frc::Subsystem("Shooter"),
	leftFront(RobotMap::leftFront),
	feederSensor(RobotMap::feederSensor),
	_leftRear(RobotMap::leftRear),
	_rightFront(RobotMap::rightFront),
	_rightRear(RobotMap::rightRear),
	_feeder(RobotMap::feeder) {

	leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	_rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	/*
	leftFront->SetControlMode(CANSpeedController::kSpeed);
	leftFront->ConfigNominalOutputVoltage(0.0, 0.0);
	leftFront->ConfigPeakOutputVoltage(12.0, -12.0);
	leftFront->SetSensorDirection(true);
	leftFront->SetP(0.05);
	leftFront->SetI(0.0);
	leftFront->SetD(0.0);
	leftFront->SetF(0.03);

	rightFront->SetControlMode(CANSpeedController::kSpeed);
	rightFront->ConfigNominalOutputVoltage(0.0, 0.0);
	rightFront->ConfigPeakOutputVoltage(12.0, -12.0);
	rightFront->SetSensorDirection(true);
	rightFront->SetP(0.05);
	rightFront->SetI(0.0);
	rightFront->SetD(0.0);
	rightFront->SetF(0.03);
	*/
}

// ==========================================================================

void Shooter::InitDefaultCommand() {
	SetDefaultCommand(new ShootDefault());
}

// ==========================================================================

void Shooter::shootFront() {
	leftFront->Set(1);
	_rightFront->Set(-1);
	/*
	leftFront->SetControlMode(CANSpeedController::kSpeed);
	leftFront->Set(RPM);
	_rightFront->SetControlMode(CANSpeedController::kSpeed);
	_rightFront->Set(-RPM);
	*/
}

// ==========================================================================

void Shooter::shootBack() {
	_leftRear->Set(-1);
	_rightRear->Set(1);
}

// ==========================================================================

void Shooter::stopFront() {
	leftFront->SetControlMode(CANSpeedController::kPercentVbus);
	leftFront->Set(0);
	_rightFront->SetControlMode(CANSpeedController::kPercentVbus);
	_rightFront->Set(0);
}

// ==========================================================================

void Shooter::stopBack() {
	_leftRear->Set(0);
	_rightRear->Set(0);
}

// ==========================================================================

void Shooter::feed() {
	_feeder->Set(-0.7);
}

// ==========================================================================

void Shooter::deFeed() {
	_feeder->Set(0.5);
}

// ==========================================================================

void Shooter::stopFeed() {
	_feeder->Set(0);
}

// ==========================================================================

void Shooter::shootDefault(float right, float left) {
	if (right > 0.1) {
		shootFront();
		shootBack();
	}
	else {
		stopFront();
		stopBack();
	}

	if ((left > 0.1 && feederSensor->GetAverageVoltage() > 4.0) || (left > 0.1 && right > 0.1)) {
		feed();
	}
	else {
		stopFeed();
	}
}

// ==========================================================================

double Shooter::getVelocity() {
	return leftFront->GetSpeed();
}

// ==========================================================================
