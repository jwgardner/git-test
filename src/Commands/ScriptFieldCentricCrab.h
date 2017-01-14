#ifndef ScriptFieldCentricCrab_H
#define ScriptFieldCentricCrab_H

#include "WPILib.h"

class ScriptFieldCentricCrab : public Command {
public:
  float twist;
  float y;
  float x;

  ScriptFieldCentricCrab(float twist, float y, float x, float timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
