#ifndef Wait_H
#define Wait_H

#include "WPILib.h"

class Wait : public Command {
public:
  Wait(double time);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
