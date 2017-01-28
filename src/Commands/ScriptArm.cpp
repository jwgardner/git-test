#include "Commands/ScriptArm.h"
#include "Robot.h"

// ==========================================================================

ScriptArm::ScriptArm(int pos)
: _pos(pos) {
	Requires(Robot::armSub);
}

// ==========================================================================

void ScriptArm::Initialize() {
	SetTimeout(0.5);
	if (_pos == 0)
		Robot::armSub->stowArm();
	if (_pos == 1)
		Robot::armSub->armUp();
	if (_pos == 2)
		Robot::armSub->armDown();
}

// ==========================================================================

void ScriptArm::Execute() {
}

// ==========================================================================

bool ScriptArm::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================

void ScriptArm::End() {
	Robot::armSub->disablePositionControl();
}

// ==========================================================================

void ScriptArm::Interrupted() {
	End();
}

// ==========================================================================
