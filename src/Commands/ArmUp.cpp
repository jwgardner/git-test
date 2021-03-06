#include "Commands/ArmUp.h"
#include "Robot.h"

// ==========================================================================

ArmUp::ArmUp()
: frc::Command() {
	Requires(Robot::armSub);
}

// ==========================================================================

void ArmUp::Initialize() {
	Robot::armSub->ArmUp();
}

// ==========================================================================

void ArmUp::Execute() {
}

// ==========================================================================

bool ArmUp::IsFinished() {
	return false;
}

// ==========================================================================

void ArmUp::End() {
	Robot::armSub->Stop();
}

// ==========================================================================

void ArmUp::Interrupted() {
	End();
}

// ==========================================================================
