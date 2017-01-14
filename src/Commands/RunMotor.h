#ifndef RunMotor_H
#define RunMotor_H

#include "WPILib.h"

class RunMotor : public Command {
public:
  CANTalon *motor;
  RunMotor(CANTalon *motor);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
