#include "ZeroYaw.h"
#include "../RobotMap.h"

ZeroYaw::ZeroYaw() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
  SetRunWhenDisabled(true);
  SetTimeout(1);
}

// Called just before this Command runs the first time
void ZeroYaw::Initialize() { RobotMap::imu->ZeroYaw(); }

// Called repeatedly when this Command is scheduled to run
void ZeroYaw::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ZeroYaw::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void ZeroYaw::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroYaw::Interrupted() {}
