#ifndef DefeedShoot_H
#define DefeedShoot_H

#include "WPILib.h"

class DefeedShoot : public Command {
public:
  DefeedShoot(double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
