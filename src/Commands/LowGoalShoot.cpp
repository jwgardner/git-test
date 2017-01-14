#include "LowGoalShoot.h"
#include "../Robot.h"
LowGoalShoot::LowGoalShoot(double timeout) {
  Requires(Robot::shooter);
  SetTimeout(timeout);
  counter = 0;
}

// Called just before this Command runs the first time
void LowGoalShoot::Initialize() {
  Robot::shooter->shootFront();
  counter = 0;
}

// Called repeatedly when this Command is scheduled to run
void LowGoalShoot::Execute() {
  counter++;
  if (counter > 10)
    Robot::shooter->shootBack();
}

// Make this return true when this Command no longer needs to run execute()
bool LowGoalShoot::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void LowGoalShoot::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowGoalShoot::Interrupted() {}
