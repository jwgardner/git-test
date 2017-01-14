#ifndef ScriptArm_H
#define ScriptArm_H

#include "WPILib.h"

class ScriptArm : public Command {
private:
  int pos;

public:
  ScriptArm(int pos);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
