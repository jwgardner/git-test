#ifndef SCRIPTGYRODRIVE_H
#define SCRIPTGYRODRIVE_H

#include "WPILib.h"
#include <Commands/Command.h>

class ScriptGyroDrive : public Command {
public:
  ScriptGyroDrive(const char *name, float x, float y, float z, float seconds);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

private:
  float _x;
  float _y;
  float _z;
  float _seconds;
};

#endif
