#include <WPILib.h>
#include <iostream>

#include "Commands/ScriptCommand.h"
#include "Modules/CommandListParser.h"

// ==========================================================================

ScriptCommand::ScriptCommand(const char *name)
: ScriptCommand(name, SmartDashboard::GetString("ScriptCommand", "")) {
}

// ==========================================================================

ScriptCommand::ScriptCommand(const char *name, std::string script)
: frc::CommandGroup(name) {
	std::cout << "ScriptCommand:" << name << std::endl;
	ParseCommands(script);
}

// ==========================================================================

void ScriptCommand::InitParameters() {
	try {
		SmartDashboard::GetString("ScriptCommand", "");
	} catch (...) {
		// SmartDashboard parameter does not exist; create it.
		SmartDashboard::PutString("ScriptCommand", "S(1)");
	}
}

// ==========================================================================

void ScriptCommand::ParseCommands(std::string script) {
	CommandListParser &parser(CommandListParser::GetInstance());
	parser.Parse(script, [this](bool parallel, Command *cmd, float timeout) {
		if (parallel) {
			if (timeout) {
				AddParallel(cmd, timeout);
			} else {
				AddParallel(cmd);
			}
		} else {
			if (timeout) {
				AddSequential(cmd, timeout);
			} else {
				AddSequential(cmd);
			}
		}
	});
}

// ==========================================================================
