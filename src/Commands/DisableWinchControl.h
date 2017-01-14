#ifndef DisableWinchControl_H
#define DisableWinchControl_H

#include "WPILib.h"

class DisableWinchControl : public Command {
public:
  DisableWinchControl();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
