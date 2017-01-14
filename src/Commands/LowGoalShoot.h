#ifndef LowGoalShoot_H
#define LowGoalShoot_H

#include "WPILib.h"

class LowGoalShoot : public Command {
public:
  int counter;
  LowGoalShoot(double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
