#include "Wait.h"
#include "../Robot.h"

Wait::Wait(double time) {
  SetTimeout(time);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
}

// Called just before this Command runs the first time
void Wait::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Wait::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool Wait::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void Wait::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Wait::Interrupted() {}
