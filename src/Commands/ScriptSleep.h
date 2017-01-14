#ifndef SCRIPTSLEEP_H
#define SCRIPTSLEEP_H

#include "WPILib.h"
#include <Commands/Command.h>

class ScriptSleep : public Command {
public:
  ScriptSleep(const char *name, float seconds);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

private:
  float _seconds;
};

#endif
