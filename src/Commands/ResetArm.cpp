#include "ResetArm.h"
#include "../Robot.h"

ResetArm::ResetArm() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
  SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void ResetArm::Initialize() { Robot::armSub->reset(); }

// Called repeatedly when this Command is scheduled to run
void ResetArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetArm::IsFinished() { return true; }

// Called once after isFinished returns true
void ResetArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetArm::Interrupted() {}
