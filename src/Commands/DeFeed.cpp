#include "DeFeed.h"
#include "../Robot.h"

DeFeed::DeFeed(double timeout) {
  Requires(Robot::shooter);
  SetTimeout(timeout);
}

// Called just before this Command runs the first time
void DeFeed::Initialize() { Robot::shooter->deFeed(); }

// Called repeatedly when this Command is scheduled to run
void DeFeed::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool DeFeed::IsFinished() {
  return IsTimedOut() ||
         !(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0);
}

// Called once after isFinished returns true
void DeFeed::End() { Robot::shooter->stopFeed(); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeFeed::Interrupted() { End(); }
