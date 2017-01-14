#ifndef SetWinchPosition_H
#define SetWinchPosition_H

#include "WPILib.h"

class SetWinchPosition : public Command {
private:
  double pos;

public:
  SetWinchPosition(int pos, bool holdPos, double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
  bool holdPos;
};

#endif
