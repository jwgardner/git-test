#pragma once

#include <Commands/Command.h>

// ==========================================================================

class DeFeed : public frc::Command {
public:
	DeFeed(double timeout);

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

// ==========================================================================
