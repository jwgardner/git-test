#ifndef DeFeed_H
#define DeFeed_H

#include "WPILib.h"

class DeFeed : public Command {
public:
  DeFeed(double timeout);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
