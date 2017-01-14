#include "ShootDefault.h"
#include "../Robot.h"

ShootDefault::ShootDefault() { Requires(Robot::shooter); }

// Called just before this Command runs the first time
void ShootDefault::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShootDefault::Execute() {
  Robot::shooter->shootDefault(Robot::oi->GetRightTrigger(),
                               Robot::oi->GetLeftTrigger());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootDefault::IsFinished() { return false; }

// Called once after isFinished returns true
void ShootDefault::End() {
  Robot::shooter->stopFront();
  Robot::shooter->stopBack();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootDefault::Interrupted() { End(); }
