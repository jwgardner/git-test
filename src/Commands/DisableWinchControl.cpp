#include "DisableWinchControl.h"
#include "../Robot.h"

DisableWinchControl::DisableWinchControl() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
}

// Called just before this Command runs the first time
void DisableWinchControl::Initialize() {
  Robot::winchSub->disablePositionControl();
}

// Called repeatedly when this Command is scheduled to run
void DisableWinchControl::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool DisableWinchControl::IsFinished() { return true; }

// Called once after isFinished returns true
void DisableWinchControl::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DisableWinchControl::Interrupted() {}
