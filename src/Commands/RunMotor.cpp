#include "RunMotor.h"

RunMotor::RunMotor(CANTalon *motor) {}

// Called just before this Command runs the first time
void RunMotor::Initialize() { RunMotor::motor = motor; }

// Called repeatedly when this Command is scheduled to run
void RunMotor::Execute() { motor->Set(1); }

// Make this return true when this Command no longer needs to run execute()
bool RunMotor::IsFinished() { return false; }

// Called once after isFinished returns true
void RunMotor::End() { motor->Set(0); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunMotor::Interrupted() { motor->Set(0); }
