#include "Commands/Feed.h"
#include "Robot.h"

// ==========================================================================

Feed::Feed(double seconds)
: _seconds(seconds), _seenBall(false){
	Requires(Robot::shooter);
}

// ==========================================================================

void Feed::Initialize() {
	SetTimeout(_seconds);
	_seenBall = false;
	Robot::shooter->shootFront();
	Robot::shooter->shootBack();
}

// ==========================================================================

void Feed::Execute() {
	if (std::abs(Robot::shooter->leftFront->GetSpeed()) > 4000)
		Robot::shooter->feed();
	if (Robot::shooter->feederSensor->GetAverageVoltage() > 4.0)
		_seenBall = true;
}

// ==========================================================================

bool Feed::IsFinished() {
	return IsTimedOut() ||
		(Robot::shooter->feederSensor->GetAverageVoltage() < 4.0 && _seenBall);
}

// ==========================================================================

void Feed::End() {
	Robot::shooter->stopFeed();
}

// ==========================================================================

void Feed::Interrupted() {
	End();
}

// ==========================================================================
