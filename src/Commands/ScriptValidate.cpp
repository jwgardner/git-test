#include "ScriptValidate.h"
#include "../Modules/CommandListParser.h"
#include "SmartDashboard/SmartDashboard.h"
#include <WPILib.h>
#include <iostream>

// ==========================================================================

ScriptValidate::ScriptValidate()
    : ScriptValidate("ScriptCommand", "ScriptValid") {}

// ==========================================================================

ScriptValidate::ScriptValidate(const char *dashboardInput,
                               const char *dashboardOutput)
    : Command("ScriptValidate"), _dashboardInput(dashboardInput),
      _dashboardOutput(dashboardOutput) {
  std::cout << GetName() << "::ctor(" << dashboardInput << ", "
            << dashboardOutput << ")" << std::endl;
  SetRunWhenDisabled(true);
}

// ==========================================================================

void ScriptValidate::Initialize() {
  // std::cout << GetName() << "::Initialize" << std::endl;
}

// ==========================================================================

void ScriptValidate::Execute() { ValidateCommands(); }

// ==========================================================================

bool ScriptValidate::IsFinished() { return true; }

// ==========================================================================

void ScriptValidate::End() {
  // std::cout << GetName() << "::End" << std::endl;
}

// ==========================================================================

void ScriptValidate::Interrupted() {
  // std::cout << GetName() << "::Interrupted" << std::endl;
}

// ==========================================================================

void ScriptValidate::ValidateCommands() {
  auto commands = SmartDashboard::GetString(_dashboardInput, "S(0)");
  CommandListParser &parser(CommandListParser::GetInstance());
  SmartDashboard::PutString(_dashboardOutput,
                            parser.IsValid(commands) ? "Valid" : "Invalid");
}

// ==========================================================================
