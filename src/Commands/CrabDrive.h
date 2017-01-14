#ifndef CRABDRIVE_H
#define CRABDRIVE_H

#include <Commands/Command.h>

class CrabDrive : public Command {
public:
  CrabDrive();
  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

private:
};

#endif
