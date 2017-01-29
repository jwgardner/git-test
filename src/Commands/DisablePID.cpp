#include "Commands/DisablePID.h"
#include "Robot.h"

// ==========================================================================

DisablePID::DisablePID() {
}

// ==========================================================================

void DisablePID::Initialize() {
	Robot::driveTrain->frontLeft->Disable();
	Robot::driveTrain->frontRight->Disable();
	Robot::driveTrain->rearLeft->Disable();
	Robot::driveTrain->rearRight->Disable();
}

// ==========================================================================

void DisablePID::Execute() {
}

// ==========================================================================

bool DisablePID::IsFinished() {
	return false;
}

// ==========================================================================

void DisablePID::End() {
	Robot::driveTrain->frontLeft->Enable();
	Robot::driveTrain->frontRight->Enable();
	Robot::driveTrain->rearLeft->Enable();
	Robot::driveTrain->rearRight->Enable();
}

// ==========================================================================

void DisablePID::Interrupted() {
	End();
}

// ==========================================================================
