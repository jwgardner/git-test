#include "Commands/DeFeed.h"
#include "Robot.h"

// ==========================================================================

DeFeed::DeFeed(double timeout) {
	Requires(Robot::shooter);
	SetTimeout(timeout);
}

// ==========================================================================

void DeFeed::Initialize() {
	Robot::shooter->deFeed();
}

// ==========================================================================

void DeFeed::Execute() {
}

// ==========================================================================

bool DeFeed::IsFinished() {
	return IsTimedOut() || !(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0);
}

// ==========================================================================

void DeFeed::End() {
	Robot::shooter->stopFeed();
}

// ==========================================================================

void DeFeed::Interrupted() {
	End();
}

// ==========================================================================
