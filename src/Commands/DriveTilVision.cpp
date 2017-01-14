#include "DriveTilVision.h"
#include "../Robot.h"

DriveTilVision::DriveTilVision(double y, double x, double twist,
                               double timeout) {
  Requires(Robot::driveTrain);
  SetTimeout(timeout);
  _x = x;
  _y = y;
  _twist = twist;
}

// Called just before this Command runs the first time
void DriveTilVision::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveTilVision::Execute() {
  Robot::driveTrain->Crab(_twist, _y, _x, false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTilVision::IsFinished() {
  return (Robot::visionBridge->GetDistance() != 0 &&
          Robot::visionBridge->GetDistance() < 100) ||
         IsTimedOut();
}

// Called once after isFinished returns true
void DriveTilVision::End() { Robot::driveTrain->Crab(0, 0, 0, false); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTilVision::Interrupted() { End(); }
