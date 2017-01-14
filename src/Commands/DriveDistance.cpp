#include "DriveDistance.h"
#include "Robot.h"

DriveDistance::DriveDistance(float driveangle, float speed, float twistangle,
                             float distance) {
  Requires(Robot::driveTrain);

  X = driveangle;
  Y = speed;
  TwistAngle = twistangle;
  Distance = distance; //*46.5;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize() { Robot::driveTrain->zeroDistanceEncoders(); }

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
  Robot::driveTrain->Crab(TwistAngle, X, Y, false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
  return Robot::driveTrain->getDistanceEncodersValues() >= Distance;
}

// Called once after isFinished returns true
void DriveDistance::End() { Robot::driveTrain->Crab(0, 0, 0, false); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() { Robot::driveTrain->Crab(0, 0, 0, false); }
