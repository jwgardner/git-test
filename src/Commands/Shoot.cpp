#include "Shoot.h"
#include "../Robot.h"

Shoot::Shoot(double timeout) {
  Requires(Robot::shooter);
  SetTimeout(timeout);
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
  Robot::shooter->shootFront();
  Robot::shooter->shootBack();
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void Shoot::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() { End(); }
