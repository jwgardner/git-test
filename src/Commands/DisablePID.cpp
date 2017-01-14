#include "DisablePID.h"
#include "Robot.h"

DisablePID::DisablePID() {}

// Called just before this Command runs the first time
void DisablePID::Initialize() {
  Robot::driveTrain->frontLeft->Disable();
  Robot::driveTrain->frontRight->Disable();
  Robot::driveTrain->rearLeft->Disable();
  Robot::driveTrain->rearRight->Disable();
}

// Called repeatedly when this Command is scheduled to run
void DisablePID::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool DisablePID::IsFinished() { return false; }

// Called once after isFinished returns true
void DisablePID::End() {
  Robot::driveTrain->frontLeft->Enable();
  Robot::driveTrain->frontRight->Enable();
  Robot::driveTrain->rearLeft->Enable();
  Robot::driveTrain->rearRight->Enable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DisablePID::Interrupted() { End(); }
