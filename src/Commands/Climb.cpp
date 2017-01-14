#include "Climb.h"
#include "../Robot.h"

Climb::Climb() { Requires(Robot::winchSub); }

// Called just before this Command runs the first time
void Climb::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute() { Robot::winchSub->climb(); }

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() { return false; }

// Called once after isFinished returns true
void Climb::End() { Robot::winchSub->stopClimb(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() { End(); }
