#ifndef ResetWinch_H
#define ResetWinch_H

#include "WPILib.h"

class ResetWinch : public Command {
public:
  ResetWinch();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
