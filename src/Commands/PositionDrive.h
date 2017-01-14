#ifndef POSITIONDRIVE_H
#define POSITIONDRIVE_H

#include "../Modules/VisionSink.h"
#include "../Modules/VisionSource.h"
#include "WPILib.h"
#include <Commands/Command.h>

class PositionDrive : public Command {
public:
  double pixels;
  PositionDrive(int offset = 0, int side = 0); // const char* name, double x,
                                               // double y, double maxspeed,
                                               // double seconds);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();

private:
  int _side;
  int _offset;
  int waiting;
  int waitingCounter;
  double _x;
  double _y;
  double _maxspeed;
  double _seconds;
  double _angle;
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
