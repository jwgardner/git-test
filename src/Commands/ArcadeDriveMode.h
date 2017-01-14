#ifndef ArcadeDriveMode_H
#define ArcadeDriveMode_H

#include "WPILib.h"

class ArcadeDriveMode : public Command {
public:
  ArcadeDriveMode();
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
