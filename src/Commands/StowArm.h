#ifndef StowArm_H
#define StowArm_H

#include "WPILib.h"

class StowArm : public Command {
public:
  StowArm();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
