#ifndef SetWheelOffsets_H
#define SetWheelOffsets_H

#include "WPILib.h"

class SetWheelOffsets : public Command {
public:
  SetWheelOffsets();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
