#include "ArmUp.h"

ArmUp::ArmUp() : Command() { Requires(Robot::armSub); }

// Called just before this Command runs the first time
void ArmUp::Initialize() { Robot::armSub->armUp(); }

// Called repeatedly when this Command is scheduled to run
void ArmUp::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ArmUp::IsFinished() { return false; }

// Called once after isFinished returns true
void ArmUp::End() { Robot::armSub->stop(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmUp::Interrupted() { Robot::armSub->stop(); }
