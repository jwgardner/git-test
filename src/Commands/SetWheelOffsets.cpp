#include "../Robot.h"
#include <Commands/SetWheelOffsets.h>

SetWheelOffsets::SetWheelOffsets() {
  SetRunWhenDisabled(true);
  SetTimeout(1);
}

// Called just before this Command runs the first time
void SetWheelOffsets::Initialize() { Robot::driveTrain->setWheelOffsets(); }

// Called repeatedly when this Command is scheduled to run
void SetWheelOffsets::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetWheelOffsets::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void SetWheelOffsets::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWheelOffsets::Interrupted() {}
