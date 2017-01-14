#include "ScriptFieldCentricCrab.h"
#include "../Robot.h"

ScriptFieldCentricCrab::ScriptFieldCentricCrab(float twist, float y, float x,
                                               float timeout) {
  ScriptFieldCentricCrab::twist = twist;
  ScriptFieldCentricCrab::y = y;
  ScriptFieldCentricCrab::x = x;
  Requires(Robot::driveTrain);
  SetTimeout(timeout);
}

// Called just before this Command runs the first time
void ScriptFieldCentricCrab::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ScriptFieldCentricCrab::Execute() {
  Robot::driveTrain->FieldCentricCrab(twist, y, x, false);
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptFieldCentricCrab::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void ScriptFieldCentricCrab::End() { Robot::driveTrain->Crab(0, 0, 0, false); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptFieldCentricCrab::Interrupted() { End(); }
