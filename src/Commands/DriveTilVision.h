#ifndef DriveTilVision_H
#define DriveTilVision_H

#include "WPILib.h"

class DriveTilVision : public Command {
public:
  double _x, _y, _twist;

  DriveTilVision(double y, double x, double twist, double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
