#ifndef Climb_H
#define Climb_H

#include "WPILib.h"

class Climb : public Command {
public:
  Climb();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
