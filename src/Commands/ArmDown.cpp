#include "ArmDown.h"

ArmDown::ArmDown() : Command() { Requires(Robot::armSub); }

// Called just before this Command runs the first time
void ArmDown::Initialize() { Robot::armSub->armDown(); }

// Called repeatedly when this Command is scheduled to run
void ArmDown::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ArmDown::IsFinished() { return false; }

// Called once after isFinished returns true
void ArmDown::End() { Robot::armSub->stop(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmDown::Interrupted() { Robot::armSub->stop(); }
