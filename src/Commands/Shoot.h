#ifndef Shoot_H
#define Shoot_H

#include "WPILib.h"

class Shoot : public Command {
public:
  Shoot(double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
