#ifndef ZeroYaw_H
#define ZeroYaw_H

#include "WPILib.h"

class ZeroYaw : public Command {
public:
  ZeroYaw();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
