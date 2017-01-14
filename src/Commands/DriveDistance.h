#ifndef DriveDistance_H
#define DriveDistance_H

#include "WPILib.h"

class DriveDistance : public Command {
public:
  DriveDistance(float speed, float driveangle, float twistangle,
                float distance);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

private:
  float X;
  float Y;
  float TwistAngle;
  float Distance;
};

#endif
