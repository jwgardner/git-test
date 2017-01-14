#include "ResetWinch.h"
#include "../Robot.h"

ResetWinch::ResetWinch() {
  Requires(Robot::winchSub);
  SetRunWhenDisabled(true);
  SetTimeout(1);
}

// Called just before this Command runs the first time
void ResetWinch::Initialize() { Robot::winchSub->reset(); }

// Called repeatedly when this Command is scheduled to run
void ResetWinch::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetWinch::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void ResetWinch::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetWinch::Interrupted() {}
