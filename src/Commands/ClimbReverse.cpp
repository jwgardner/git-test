#include "ClimbReverse.h"
#include "../Robot.h"

ClimbReverse::ClimbReverse() { Requires(Robot::winchSub); }

// Called just before this Command runs the first time
void ClimbReverse::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbReverse::Execute() { Robot::winchSub->climbReverse(); }

// Make this return true when this Command no longer needs to run execute()
bool ClimbReverse::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbReverse::End() { Robot::winchSub->stopClimb(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbReverse::Interrupted() { End(); }
