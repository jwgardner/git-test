#include "ScriptGyroDrive.h"
#include "../Robot.h"
#include <iostream>

ScriptGyroDrive::ScriptGyroDrive(const char *name, float x, float y, float z,
                                 float seconds)
    : Command(name), _x(x), _y(y), _z(z), _seconds(seconds) {
  std::cout << GetName() << "::ctor(" << x << ", " << y << ", " << z << ", "
            << seconds << ")" << std::endl;
  Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void ScriptGyroDrive::Initialize() {
  std::cout << GetName() << "::Initialize" << std::endl;
  SetTimeout(_seconds);
  Robot::driveTrain->enableSpeedControl();
}

// Called repeatedly when this Command is scheduled to run
void ScriptGyroDrive::Execute() {
  Robot::driveTrain->GyroCrab(_z, _x, _y, false);
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptGyroDrive::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void ScriptGyroDrive::End() {
  std::cout << GetName() << "::End" << std::endl;
  Robot::driveTrain->Crab(0, 0, 0, false);
  Robot::driveTrain->disableSpeedControl();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptGyroDrive::Interrupted() {
  std::cout << GetName() << "::Interrupted" << std::endl;
  Robot::driveTrain->Crab(0, 0, 0, false);
  Robot::driveTrain->disableSpeedControl();
}
