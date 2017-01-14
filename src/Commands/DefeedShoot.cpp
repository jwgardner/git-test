#include "DefeedShoot.h"
#include "../Robot.h"

DefeedShoot::DefeedShoot(double timeout) {
  Requires(Robot::shooter);
  SetTimeout(timeout);
}

// Called just before this Command runs the first time
void DefeedShoot::Initialize() { Robot::shooter->deFeed(); }

// Called repeatedly when this Command is scheduled to run
void DefeedShoot::Execute() {
  if (!(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0)) {
    Robot::shooter->shootFront();
    Robot::shooter->shootBack();
    Robot::shooter->stopFeed();
  }
  if (Robot::oi->GetLeftTrigger() > 0.1) {
    Robot::shooter->feed();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool DefeedShoot::IsFinished() {
  return IsTimedOut() ||
         (!(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0) &&
          std::abs(Robot::shooter->leftFront->GetSpeed()) > 4000);
}

// Called once after isFinished returns true
void DefeedShoot::End() { Robot::shooter->stopFeed(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DefeedShoot::Interrupted() { Robot::shooter->stopFeed(); }
