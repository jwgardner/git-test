#include "SetWheelsTwist.h"
#include "../Robot.h"

SetWheelsTwist::SetWheelsTwist(double timeout) {
  Requires(Robot::driveTrain);
  SetTimeout(timeout);
}

// Called just before this Command runs the first time
void SetWheelsTwist::Initialize() { Robot::driveTrain->PositionModeTwist(0); }

// Called repeatedly when this Command is scheduled to run
void SetWheelsTwist::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetWheelsTwist::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void SetWheelsTwist::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWheelsTwist::Interrupted() {}
