#include "ScriptCamDrive.h"
#include "../Robot.h"
#include <iostream>

#define TIME 10

ScriptCamDrive::ScriptCamDrive(const char *name, double x, double y,
                               double maxspeed, double seconds, int side)
    : Command(name), _x(x), _y(y), _maxspeed(maxspeed), _seconds(seconds) {
  std::cout << GetName() << "::ctor(" << x << ", " << y << ", " << maxspeed
            << ", " << seconds << ")" << std::endl;
  Requires(Robot::driveTrain);

  pid = new PIDController(0, 0, 0, 0, &visionSource, &visionSink);
  _side = side;
}

// Called just before this Command runs the first time
void ScriptCamDrive::Initialize() {
  std::cout << GetName() << "::Initialize" << std::endl;
  if (_seconds == 0) {
    SetTimeout(16);
    _returnQuick = true;
  } else {
    SetTimeout(_seconds);
    _returnQuick = false;
  }
  _counter = 0;
  _angle = Robot::gyroSub->PIDGet();
  _angle /= 90.;
  _angle = floor(_angle + .5); // round
  _angle *= 90.;
  _p = SmartDashboard::GetNumber("vision P", .3);
  _i = SmartDashboard::GetNumber("vision I", .3);
  _d = SmartDashboard::GetNumber("vision D", .3);
  pid->SetPID(_p / 100, _i / 100, _d / 100);
  _tol = SmartDashboard::GetNumber("vision tol", 15);
  _center = SmartDashboard::GetNumber("vision center", 25.0);
  pid->SetAbsoluteTolerance(_tol);
  pid->SetSetpoint(_center);
  pid->Enable();
  pid->SetOutputRange(-0.25, 0.25);
  _time = 0;
  Robot::driveTrain->enableSpeedControl();
}

// Called repeatedly when this Command is scheduled to run
void ScriptCamDrive::Execute() {
  _offset = Robot::visionBridge->GetPosition(_side);
  if (std::abs(_offset - _center) < _tol) {
    _counter++;
  } else {
    _counter = 0;
  }
  //_offset -= _center;
  // if(fabs(_offset) <= _tol)
  //    _offset = 0;
  double speed = -visionSink.GetValue();
  // if (speed > 0) speed += 0.1;
  // else speed -= 0.1;
  if (speed < 0.01 && speed > -0.01)
    speed = 0.01;
  // speed = std::min(_maxspeed, std::max(-_maxspeed, speed));
  SmartDashboard::PutNumber("vision pid value", speed);
  Robot::driveTrain->Crab(speed, _x, _y, false);
  // if(fabs(_offset) <= _tol)
  //    _time++;
  // else
  //    _time = 0;
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptCamDrive::IsFinished() {
  // if (_x == 0.0 && _time > TIME)    //fabs(_offset) <= _tol)
  //    return true;
  return IsTimedOut() || (_returnQuick && _counter > 10);
}

// Called once after isFinished returns true
void ScriptCamDrive::End() {
  std::cout << GetName() << "::End" << std::endl;
  Robot::driveTrain->Crab(0, 0, 0, false);
  pid->Disable();
  Robot::driveTrain->disableSpeedControl();
  _counter = 0;
  // delete pid;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptCamDrive::Interrupted() {
  std::cout << GetName() << "::Interrupted" << std::endl;
  Robot::driveTrain->Crab(0, 0, 0, false);
  pid->Disable();
  Robot::driveTrain->disableSpeedControl();
  _counter = 0;
  // delete pid;
}
