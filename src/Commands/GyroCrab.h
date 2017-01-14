#ifndef GYROCRAB_H
#define GYROCRAB_H

#include <Commands/Command.h>

class GyroCrab : public Command {
public:
  GyroCrab();
  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

private:
  float angle;
};

#endif
