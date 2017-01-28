#pragma once

#include <Commands/CommandGroup.h>
#include <string>

// ==========================================================================

class ScriptCommand : public frc::CommandGroup {
public:
	ScriptCommand(const char *name);
	ScriptCommand(const char *name, std::string commands);

	static void InitParameters();

protected:
	void ParseCommands(std::string commands);

private:
};

// ==========================================================================
