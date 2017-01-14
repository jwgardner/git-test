#include "FieldCentric.h"
#include "Robot.h"

FieldCentric::FieldCentric() : Command("Field Centric") {
  std::cout << "FieldCentric::FieldCentric" << std::endl;

  Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void FieldCentric::Initialize() { Robot::driveTrain->CrabInit(); }

// Called repeatedly when this Command is scheduled to run
void FieldCentric::Execute() {
  float x = Robot::oi->GetJoystickX();
  float y = Robot::oi->GetJoystickY();
  float z = Robot::oi->GetJoystickZ();
  // std::cout << "X " << x << ", Y " << y << ", Z " << z << std::endl;
  Robot::driveTrain->FieldCentricCrab(z, -y, x, true);
  // Robot::driveTrain->GyroCrab(0, -y, x, true);
  // Robot::driveTrain->FieldCentricCrab(z,-y,x, true);
}

// Make this return true when this Command no longer needs to run Execute.
bool FieldCentric::IsFinished() { return false; }

// Called once after isFinished returns true
void FieldCentric::End() {}

// Called when another command which requires this subsystem is scheduled to run
void FieldCentric::Interrupted() { End(); }
