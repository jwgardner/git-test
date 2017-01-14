#ifndef ResetArm_H
#define ResetArm_H

#include "WPILib.h"

class ResetArm : public Command {
public:
  ResetArm();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
