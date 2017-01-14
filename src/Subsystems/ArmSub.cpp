#include "ArmSub.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

ArmSub::ArmSub() : Subsystem("Arm") {
  armMotor = RobotMap::armMotor;

  armMotor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
  armMotor->SetP(0.8);
  armMotor->SetI(0.005);
  armMotor->SetD(0.05);
  armMotor->SetF(0.0);
  // armMotor->SetSensorDirection(true);
  armMotor->SetSetpoint(0.0);
  armMotor->ConfigPeakOutputVoltage(10.0, -10.0);
  armMotor->SetControlMode(CANSpeedController::kPercentVbus);
  armMotor->Set(0);
}

void ArmSub::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void ArmSub::armDown() {
  armMotor->SetControlMode(CANSpeedController::kPosition);
  armMotor->SetSetpoint(0.67 + offset);
}
void ArmSub::stop() {
  // ArmSub::armMotor->Set(0);
}
void ArmSub::armUp() {
  armMotor->SetControlMode(CANSpeedController::kPosition);
  armMotor->SetSetpoint(0.43 + offset);
}

void ArmSub::stowArm() {
  armMotor->SetControlMode(CANSpeedController::kPosition);
  armMotor->SetSetpoint(0.0 + offset);
}

void ArmSub::readPos() {
  SmartDashboard::PutNumber("Arm Position", armMotor->GetPosition() - offset);
}

void ArmSub::reset() { armMotor->SetPosition(0.0); }

void ArmSub::setOffset(double offset) { ArmSub::offset = offset; }

void ArmSub::disablePositionControl() {
  armMotor->SetControlMode(CANSpeedController::kPercentVbus);
  armMotor->Set(0);
}
