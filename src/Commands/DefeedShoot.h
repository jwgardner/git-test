#pragma once

#include <Commands/Command.h>

// ==========================================================================

class DefeedShoot : public frc::Command {
public:
	DefeedShoot(double timeout);

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

// ==========================================================================
