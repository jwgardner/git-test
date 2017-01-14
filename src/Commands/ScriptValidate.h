#ifndef SCRIPTVALIDATE_H
#define SCRIPTVALIDATE_H

#include <Commands/Command.h>
#include <string>

// ==========================================================================

class ScriptValidate : public Command {
public:
  ScriptValidate();
  ScriptValidate(const char *dashboardInput, const char *dashboardOutput);

  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

protected:
  void ValidateCommands();

private:
  std::string _dashboardInput;
  std::string _dashboardOutput;
};

// ==========================================================================

#endif
