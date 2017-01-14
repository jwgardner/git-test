#include "ScriptArm.h"
#include "../Robot.h"

ScriptArm::ScriptArm(int pos) {
  Requires(Robot::armSub);
  SetTimeout(0.5);
  ScriptArm::pos = pos;
}

// Called just before this Command runs the first time
void ScriptArm::Initialize() {
  if (pos == 0)
    Robot::armSub->stowArm();
  if (pos == 1)
    Robot::armSub->armUp();
  if (pos == 2)
    Robot::armSub->armDown();
}

// Called repeatedly when this Command is scheduled to run
void ScriptArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ScriptArm::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void ScriptArm::End() { Robot::armSub->disablePositionControl(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptArm::Interrupted() { End(); }
