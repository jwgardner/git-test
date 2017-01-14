#include "PositionDrive.h"
#include "../Robot.h"
#include <iostream>

#define TIME 10

PositionDrive::PositionDrive(int offset, int side) // const char* name, double
                                                   // x, double y, double
                                                   // maxspeed, double seconds)
    : Command(""),
      _x(0),
      _y(0),
      _maxspeed(0.35),
      _seconds(10) {
  // std::cout << GetName() << "::ctor(" << x << ", " << y << ", " << maxspeed
  // << ", " << seconds << ")" << std::endl;
  Requires(Robot::driveTrain);
  _offset = offset;
  _side = side;
}

// Called just before this Command runs the first time
void PositionDrive::Initialize() {
  std::cout << GetName() << "::Initialize" << std::endl;
  if (_seconds == 0) {
    // SetTimeout(16);
    _returnQuick = true;
  } else {
    // SetTimeout(_seconds);
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
  _tol = SmartDashboard::GetNumber("vision tol", 15);
  _center = SmartDashboard::GetNumber("vision center", 25.0);
  _time = 0;
  Robot::driveTrain->enablePositionControl();
  pixels = 0;
  waiting = 0;
  waitingCounter = 0;
}

// Called repeatedly when this Command is scheduled to run
void PositionDrive::Execute() {
  // auto gyroPos = RobotMap::imu->GetYaw();
  auto flPos = RobotMap::driveTrainFrontLeftDrive->GetPosition();
  auto frPos = RobotMap::driveTrainFrontRightDrive->GetPosition();
  auto rlPos = RobotMap::driveTrainRearLeftDrive->GetPosition();
  auto rrPos = RobotMap::driveTrainRearRightDrive->GetPosition();
  if (std::fabs(flPos - RobotMap::driveTrainFrontLeftDrive->GetSetpoint()) <
          0.002 ||
      std::fabs(frPos - RobotMap::driveTrainFrontRightDrive->GetSetpoint()) <
          0.002 ||
      std::fabs(rlPos - RobotMap::driveTrainRearLeftDrive->GetSetpoint()) <
          0.002 ||
      std::fabs(rrPos - RobotMap::driveTrainRearRightDrive->GetSetpoint()) <
          0.002)
    waitingCounter++;
  else
    waitingCounter = 0;
  if (waitingCounter > 5) {
    waiting = 0;
    waitingCounter = 0;
  }
  SmartDashboard::PutBoolean("Waiting", waiting);
  SmartDashboard::PutNumber("Waiting counter", waitingCounter);
  pixels = Robot::visionBridge->GetPosition(_side) -
           SmartDashboard::GetNumber("vision center", 40) - _offset;
  if (std::abs(pixels) < _tol)
    _counter++;
  else
    _counter = 0;
  pixels *= 0.1;
  SmartDashboard::PutNumber("Pixels", pixels);

  SmartDashboard::PutNumber("Front Left Drive Position", flPos);
  auto desiredAngle = SmartDashboard::GetNumber("Twist Angle", 0);
  auto angleError = desiredAngle + pixels;
  angleError *= (101.3 / 9.9 / 360);
  if (!waiting) {
    RobotMap::driveTrainFrontLeftDrive->SetSetpoint(flPos - angleError);
    RobotMap::driveTrainFrontRightDrive->SetSetpoint(frPos - angleError);
    RobotMap::driveTrainRearLeftDrive->SetSetpoint(rlPos - angleError);
    RobotMap::driveTrainRearRightDrive->SetSetpoint(rrPos - angleError);
  }
  waiting++;
  if (waiting > 20)
    waiting = 0;

  SmartDashboard::PutNumber("Angle Error", angleError);
  Robot::driveTrain->PositionModeTwist(0);
}

// Make this return true when this Command no longer needs to run execute()
bool PositionDrive::IsFinished() {
  // if (_x == 0.0 && _time > TIME)    //fabs(_offset) <= _tol)
  //    return true;
  return IsTimedOut() || _counter > 5;
}

// Called once after isFinished returns true
void PositionDrive::End() {
  std::cout << GetName() << "::End" << std::endl;
  Robot::driveTrain->Crab(0, 0, 0, false);
  Robot::driveTrain->disableSpeedControl();
  _counter = 0;
  // delete pid;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionDrive::Interrupted() {
  std::cout << GetName() << "::Interrupted" << std::endl;
  Robot::driveTrain->Crab(0, 0, 0, false);
  Robot::driveTrain->disableSpeedControl();
  _counter = 0;
  // delete pid;
}
