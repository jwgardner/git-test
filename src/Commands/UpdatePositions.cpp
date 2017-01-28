#include "Commands/UpdatePositions.h"
#include <SmartDashboard/SmartDashboard.h>
#include "Robot.h"
#include "RobotMap.h"

UpdatePositions::UpdatePositions() {
	SetRunWhenDisabled(true);
}

// ==========================================================================

void UpdatePositions::Initialize() {
}

// ==========================================================================

void UpdatePositions::Execute() {
	Robot::armSub->readPos();
	Robot::winchSub->readPos();
	Robot::driveTrain->updateDistanceEncoders();
	SmartDashboard::PutNumber("feeder sensor", RobotMap::feederSensor->GetAverageVoltage());
	SmartDashboard::PutBoolean("Shooter Raised", Robot::winchSub->shooterRaised);
	SmartDashboard::PutNumber("Gyro Yaw", RobotMap::imu->GetYaw());
	SmartDashboard::PutNumber("Vision Position", Robot::visionBridge->GetPosition(0));
	SmartDashboard::PutNumber("Vision Distance", Robot::visionBridge->GetDistance());
}

// ==========================================================================

bool UpdatePositions::IsFinished() {
	return false;
}

// ==========================================================================

void UpdatePositions::End() {
}

// ==========================================================================

void UpdatePositions::Interrupted() {
}

// ==========================================================================
