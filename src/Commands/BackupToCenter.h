#ifndef BackupToCenter_H
#define BackupToCenter_H

#include "WPILib.h"

class BackupToCenter : public Command {
public:
  BackupToCenter();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
