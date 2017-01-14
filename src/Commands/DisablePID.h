#ifndef DisablePID_H
#define DisablePID_H

#include "WPILib.h"

class DisablePID : public Command {
public:
  DisablePID();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
