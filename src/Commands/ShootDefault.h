#ifndef ShootDefault_H
#define ShootDefault_H

#include "WPILib.h"

class ShootDefault : public Command {
public:
  ShootDefault();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
