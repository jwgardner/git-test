#include "Subsystems/WinchSub.h"
#include <SmartDashboard/SmartDashboard.h>
#include "RobotMap.h"

const bool WinchSub::angleSensor = 1;

// ==========================================================================

WinchSub::WinchSub()
:	frc::Subsystem("ExampleSubsystem") {
	_motor = RobotMap::winchMotor;
	_shooterSensor = RobotMap::winchPot;
	if (angleSensor) {
		shooter = RobotMap::shooterWinch;
		// shooter->SetSetpoint(3.3);
		_shooterRaised = false;
		// shooter->Enable();
	}
	else {
		_motor->SetControlMode(CANSpeedController::kPosition);
		_motor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		//_motor->SetSensorDirection(true);
		_motor->SetP(0.8);
		_motor->SetI(0.0);
		_motor->SetD(0.05);
		_motor->SetF(0.0);
		_motor->Enable();
		_motor->ConfigPeakOutputVoltage(6.0, -6.0);
	}
}

// ==========================================================================

void WinchSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// ==========================================================================

bool WinchSub::ShooterIsRaised() const {
	return _shooterRaised;
}

// ==========================================================================

void WinchSub::setPos(double pos) {
	if (angleSensor) {
		shooter->Enable();
		shooter->SetSetpoint(pos);
	}
	else {
		_motor->SetControlMode(CANSpeedController::kPosition);
		_motor->SetSetpoint(pos);
	}

	if (pos < 0.2) {
		_shooterRaised = true;
	}
	else {
		_shooterRaised = false;
	}
}

// ==========================================================================

void WinchSub::disablePositionControl() {
	if (angleSensor) {
		shooter->Disable();
	}
	else {
		_motor->SetControlMode(CANSpeedController::kPercentVbus);
	}
}

// ==========================================================================

void WinchSub::readPos() {
	SmartDashboard::PutNumber("Winch Position", _motor->GetPosition());
	SmartDashboard::PutNumber("Winch Angle", _shooterSensor->GetAverageVoltage());
}

// ==========================================================================

void WinchSub::reset() {
	_motor->SetPosition(0.0);
}

// ==========================================================================

void WinchSub::climb() {
	_motor->SetControlMode(CANSpeedController::kPercentVbus);
	_motor->Set(1);
}

// ==========================================================================

void WinchSub::climbReverse() {
	_motor->SetControlMode(CANSpeedController::kPercentVbus);
	_motor->Set(-1);
}

// ==========================================================================

void WinchSub::stopClimb() {
	_motor->Set(0);
}

// ==========================================================================
