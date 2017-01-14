#include "UnwindWheels.h"
#include "Robot.h"

UnwindWheels::UnwindWheels() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::driveTrain);

  // eg. Requires(chassis);
}

// Called just before this Command runs the first time
void UnwindWheels::Initialize() {
  SmartDashboard::PutString("Unwinding", "true");
  // bool doneUnwinding = false;
}

// Called repeatedly when this Command is scheduled to run
void UnwindWheels::Execute() {
  Robot::driveTrain->unwind();
  // Robot::driveTrain->unwind(Robot::oi->GetJoystickY(),
  // Robot::oi->GetJoystickX());
}

// Make this return true when this Command no longer needs to run execute()
bool UnwindWheels::IsFinished() { return false; }

// Called once after isFinished returns true
void UnwindWheels::End() {
  SmartDashboard::PutString("Unwinding", "false");
  Robot::driveTrain->doneunwind();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UnwindWheels::Interrupted() {
  SmartDashboard::PutString("Unwinding", "false");
  Robot::driveTrain->doneunwind();
}
