#include "ScriptCommand.h"
#include "../Modules/CommandListParser.h"
#include "WPILib.h"
#include "iostream"

// ==========================================================================

ScriptCommand::ScriptCommand(const char *name)
    : ScriptCommand(name, SmartDashboard::GetString("ScriptCommand", "")) {}

// ==========================================================================

ScriptCommand::ScriptCommand(const char *name, std::string commands)
    : CommandGroup(name) {
  std::cout << "ScriptCommand:" << name << std::endl;
  ParseCommands(commands);
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

void ScriptCommand::ParseCommands(std::string commands) {
  CommandListParser &parser(CommandListParser::GetInstance());

  parser.Parse(commands, [this](bool p, Command *c, float t) {
    if (p) {
      if (t) {
        AddParallel(c, t);
      } else {
        AddParallel(c);
      }
    } else {
      if (t) {
        AddSequential(c, t);
      } else {
        AddSequential(c);
      }
    }
  });
}

// ==========================================================================
