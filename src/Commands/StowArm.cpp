#include "StowArm.h"
#include "Robot.h"

StowArm::StowArm() {
  Requires(Robot::armSub);
  SetTimeout(1);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
}

// Called just before this Command runs the first time
void StowArm::Initialize() { Robot::armSub->stowArm(); }

// Called repeatedly when this Command is scheduled to run
void StowArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool StowArm::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void StowArm::End() { Robot::armSub->disablePositionControl(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StowArm::Interrupted() { End(); }
