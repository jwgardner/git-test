#ifndef UpdatePositions_H
#define UpdatePositions_H

#include "WPILib.h"

class UpdatePositions : public Command {
public:
  UpdatePositions();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
