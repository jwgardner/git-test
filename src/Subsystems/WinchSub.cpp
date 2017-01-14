#include "WinchSub.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

const bool WinchSub::angleSensor = 1;

WinchSub::WinchSub() : Subsystem("ExampleSubsystem") {
  motor = RobotMap::winchMotor;
  shooterSensor = RobotMap::winchPot;
  if (angleSensor) {
    shooter = RobotMap::shooterWinch;
    // shooter->SetSetpoint(3.3);
    shooterRaised = false;
    // shooter->Enable();
  } else {
    motor->SetControlMode(CANSpeedController::kPosition);
    motor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
    // motor->SetSensorDirection(true);
    motor->SetP(0.8);
    motor->SetI(0.0);
    motor->SetD(0.05);
    motor->SetF(0.0);
    motor->Enable();
    motor->ConfigPeakOutputVoltage(6.0, -6.0);
  }
}

void WinchSub::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void WinchSub::setPos(double pos) {
  if (angleSensor) {
    shooter->Enable();
    shooter->SetSetpoint(pos);
  } else {
    motor->SetControlMode(CANSpeedController::kPosition);
    motor->SetSetpoint(pos);
  }

  if (pos < 0.2) {
    shooterRaised = true;
  } else {
    shooterRaised = false;
  }
}

void WinchSub::disablePositionControl() {
  if (angleSensor) {
    shooter->Disable();
  } else {
    motor->SetControlMode(CANSpeedController::kPercentVbus);
  }
}

void WinchSub::readPos() {
  SmartDashboard::PutNumber("Winch Position", motor->GetPosition());
  SmartDashboard::PutNumber("Winch Angle", shooterSensor->GetAverageVoltage());
}

void WinchSub::reset() { motor->SetPosition(0.0); }

void WinchSub::climb() {
  motor->SetControlMode(CANSpeedController::kPercentVbus);
  motor->Set(1);
}

void WinchSub::stopClimb() { motor->Set(0); }
