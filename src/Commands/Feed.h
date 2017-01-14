#ifndef Feed_H
#define Feed_H

#include "WPILib.h"

class Feed : public Command {

private:
  double Timeout;
  bool seenBall;

public:
  Feed(double Timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
