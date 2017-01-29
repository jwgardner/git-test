#include "Commands/DefeedShoot.h"
#include "Robot.h"

// ==========================================================================

DefeedShoot::DefeedShoot(double timeout) {
	Requires(Robot::shooter);
	SetTimeout(timeout);
}

// ==========================================================================

void DefeedShoot::Initialize() {
	Robot::shooter->deFeed();
}

// ==========================================================================

void DefeedShoot::Execute() {
	if (!(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0)) {
		Robot::shooter->shootFront();
		Robot::shooter->shootBack();
		Robot::shooter->stopFeed();
	}
	if (Robot::oi->GetLeftTrigger() > 0.1) {
		Robot::shooter->feed();
	}
}

// ==========================================================================

bool DefeedShoot::IsFinished() {
	return IsTimedOut() ||
		(!(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0) &&
		std::abs(Robot::shooter->leftFront->GetSpeed()) > 4000);
}

// ==========================================================================

void DefeedShoot::End() {
	Robot::shooter->stopFeed();
}

// ==========================================================================

void DefeedShoot::Interrupted() {
	End();
}

// ==========================================================================
