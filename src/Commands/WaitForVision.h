#ifndef WaitForVision_H
#define WaitForVision_H

#include "WPILib.h"

class WaitForVision : public Command {
public:
  WaitForVision();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
