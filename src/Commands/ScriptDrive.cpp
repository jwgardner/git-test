#include "Commands/ScriptDrive.h"
#include "Modules/Logger.h"
#include "Robot.h"

// ==========================================================================

ScriptDrive::ScriptDrive(std::string name, float x, float y, float z, float seconds)
: frc::Command(name), _x(x), _y(y), _z(z), _seconds(seconds) {
	char szParams[64];
	sprintf(szParams, "(%f, %f, %f, %f)", x, y, z, seconds);
	LOG(GetName() + "::ctor" + szParams);

	Requires(Robot::driveTrain);
}

// ==========================================================================

void ScriptDrive::Initialize() {
	LOG(GetName() + "::Initialize");
	SetTimeout(_seconds);
	Robot::driveTrain->enableSpeedControl();
}

// ==========================================================================

void ScriptDrive::Execute() {
	Robot::driveTrain->Crab(_z, _x, _y, false);
}

// ==========================================================================

bool ScriptDrive::IsFinished() { return IsTimedOut(); }

// ==========================================================================

void ScriptDrive::End() {
	LOG(GetName() + "::End");
	_Cleanup();
}

// ==========================================================================

void ScriptDrive::Interrupted() {
	LOG(GetName() + "::Interrupted");
	_Cleanup();
}

// ==========================================================================

void ScriptDrive::_Cleanup() {
	Robot::driveTrain->Crab(0, 0, 0, false);
	Robot::driveTrain->disableSpeedControl();
}

// ==========================================================================
