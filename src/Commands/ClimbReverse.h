#ifndef Climb_Reverse_H
#define Climb_Reverse_H

#include "WPILib.h"

class ClimbReverse : public Command {
public:
ClimbReverse();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
