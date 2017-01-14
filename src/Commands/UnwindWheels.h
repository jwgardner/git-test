#ifndef UnwindWheels_H
#define UnwindWheels_H

#include "WPILib.h"

class UnwindWheels : public Command {
public:
  UnwindWheels();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

private:
  bool doneUnwinding;
};

#endif
