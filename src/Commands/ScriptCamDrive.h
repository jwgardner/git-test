#ifndef SCRIPTCAMDRIVE_H
#define SCRIPTCAMDRIVE_H

#include "../Modules/VisionSink.h"
#include "../Modules/VisionSource.h"
#include "WPILib.h"
#include <Commands/Command.h>

class ScriptCamDrive : public Command {
public:
  ScriptCamDrive(const char *name, double x, double y, double maxspeed,
                 double seconds, int side);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
  VisionSource visionSource;
  VisionSink visionSink;
  PIDController *pid;

private:
  int _side;
  double _x;
  double _y;
  double _maxspeed;
  double _seconds;
  double _angle;
  double _offset;
  double _p;
  double _i;
  double _d;
  double _tol;
  double _center;
  int _time;
  bool _returnQuick;
  int _counter;
};

#endif
