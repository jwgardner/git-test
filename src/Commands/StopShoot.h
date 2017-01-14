#ifndef StopShoot_H
#define StopShoot_H

#include "WPILib.h"

class StopShoot : public Command {
public:
  StopShoot();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
