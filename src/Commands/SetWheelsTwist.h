#ifndef SetWheelsTwist_H
#define SetWheelsTwist_H

#include "WPILib.h"

class SetWheelsTwist : public Command {
public:
  SetWheelsTwist(double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
