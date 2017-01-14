#include "ArcadeDriveMode.h"
#include "../Robot.h"

ArcadeDriveMode::ArcadeDriveMode() { Requires(Robot::driveTrain); }

// Called just before this Command runs the first time
void ArcadeDriveMode::Initialize() { Robot::driveTrain->SetWheelsStraight(); }

// Called repeatedly when this Command is scheduled to run
void ArcadeDriveMode::Execute() {
  Robot::driveTrain->ArcadeDriveMode(Robot::oi->GetJoystickY(),
                                     Robot::oi->GetJoystickX());
}

// Make this return true when this Command no longer needs to run execute()
bool ArcadeDriveMode::IsFinished() { return false; }

// Called once after isFinished returns true
void ArcadeDriveMode::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcadeDriveMode::Interrupted() {}
