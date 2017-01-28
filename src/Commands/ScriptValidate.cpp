#include <WPILib.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>

#include "Commands/ScriptValidate.h"
#include "Modules/CommandListParser.h"
#include "Modules/ScriptCommandFactory.h"

// ==========================================================================

ScriptValidate::ScriptValidate()
: ScriptValidate("ScriptCommand", "ScriptValid") {
}

// ==========================================================================

ScriptValidate::ScriptValidate(std::string dashboardInput, std::string dashboardOutput)
: Command("ScriptValidate"), _dashboardInput(dashboardInput), _dashboardOutput(dashboardOutput) {
	std::cout << GetName() << "::ctor(" << dashboardInput << ", " << dashboardOutput << ")" << std::endl;
	SetRunWhenDisabled(true);
}

// ==========================================================================

void ScriptValidate::Initialize() {
	//std::cout << GetName() << "::Initialize" << std::endl;
}

// ==========================================================================

void ScriptValidate::Execute() {
	ValidateCommands();
}

// ==========================================================================

bool ScriptValidate::IsFinished() {
	return true;
}

// ==========================================================================

void ScriptValidate::End() {
	//std::cout << GetName() << "::End" << std::endl;
}

// ==========================================================================

void ScriptValidate::Interrupted() {
	//std::cout << GetName() << "::Interrupted" << std::endl;
}

// ==========================================================================

void ScriptValidate::ValidateCommands() {
	CommandListParser& parser(CommandListParser::GetInstance());
	auto script = SmartDashboard::GetString(_dashboardInput, "S(0)");
	auto valid = parser.IsValid(script);
	SmartDashboard::PutString(_dashboardOutput, valid ? "Valid" : "Invalid");
	if (valid) {
		ScriptCommandFactory::GetInstance().SetBlueprint(script);
	}
}

// ==========================================================================
