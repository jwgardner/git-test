#ifndef SCRIPTCOMMAND_H
#define SCRIPTCOMMAND_H

#include "Commands/CommandGroup.h"
#include "string"

// ==========================================================================

class ScriptCommand : public CommandGroup {
public:
  ScriptCommand(const char *name);
  ScriptCommand(const char *name, std::string commands);

  static void InitParameters();

protected:
  void ParseCommands(std::string commands);

private:
};

// ==========================================================================

#endif
