#include "GyroCrab.h"
#include "../Robot.h"

// keeps robot square to the edge of the field that is is most square
// when command is first started

GyroCrab::GyroCrab() : Command("Crab Drive") {
  std::cout << "GyroCrab::GyroCrab" << std::endl;

  Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void GyroCrab::Initialize() {
  angle = Robot::gyroSub->PIDGet();
  angle /= 90.;
  angle = floor(angle + .5); // round
  angle *= 90.;
}

// Called repeatedly when this Command is scheduled to run
void GyroCrab::Execute() {
  float x = Robot::oi->GetJoystickX();
  float y = Robot::oi->GetJoystickY();
  Robot::driveTrain->GyroCrab(angle, -y, x, true);
}

// Make this return true when this Command no longer needs to run Execute.
bool GyroCrab::IsFinished() { return false; }

// Called once after isFinished returns true
void GyroCrab::End() {}

// Called when another command which requires this subsystem is scheduled to run
void GyroCrab::Interrupted() { End(); }
