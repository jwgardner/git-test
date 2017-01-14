#include "UpdatePositions.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

UpdatePositions::UpdatePositions() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
  SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void UpdatePositions::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void UpdatePositions::Execute() {
  Robot::armSub->readPos();
  Robot::winchSub->readPos();
  Robot::driveTrain->updateDistanceEncoders();
  SmartDashboard::PutNumber("feeder sensor",
                            RobotMap::feederSensor->GetAverageVoltage());
  SmartDashboard::PutBoolean("Shooter Raised", Robot::winchSub->shooterRaised);
  SmartDashboard::PutNumber("Gyro Yaw", RobotMap::imu->GetYaw());
  SmartDashboard::PutNumber("Vision Position",
                            Robot::visionBridge->GetPosition(0));
  SmartDashboard::PutNumber("Vision Distance",
                            Robot::visionBridge->GetDistance());
}

// Make this return true when this Command no longer needs to run execute()
bool UpdatePositions::IsFinished() { return false; }

// Called once after isFinished returns true
void UpdatePositions::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpdatePositions::Interrupted() {}
