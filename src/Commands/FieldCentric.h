#ifndef FIELDCENTRIC_H
#define FIELDCENTRIC_H

#include <Commands/Command.h>

class FieldCentric : public Command {
public:
  FieldCentric();
  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

private:
};

#endif
