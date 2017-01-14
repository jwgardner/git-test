#include "WaitForVision.h"
#include "Robot.h"

WaitForVision::WaitForVision() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
}

// Called just before this Command runs the first time
void WaitForVision::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WaitForVision::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool WaitForVision::IsFinished() {
  return Robot::visionBridge->GetDistance() !=
         0; // || Robot::visionBridge->GetPosition(1) != 0;
}

// Called once after isFinished returns true
void WaitForVision::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForVision::Interrupted() {}
