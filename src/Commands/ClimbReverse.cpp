#include "Commands/ClimbReverse.h"
#include "Robot.h"

// ==========================================================================

ClimbReverse::ClimbReverse() {
	Requires(Robot::winchSub);
}

// ==========================================================================

void ClimbReverse::Initialize() {
}

// ==========================================================================

void ClimbReverse::Execute() {
	Robot::winchSub->climbReverse();
}

// ==========================================================================

bool ClimbReverse::IsFinished() {
	return false;
}

// ==========================================================================

void ClimbReverse::End() {
	Robot::winchSub->stopClimb();
}

// ==========================================================================

void ClimbReverse::Interrupted() {
	End();
}

// ==========================================================================
