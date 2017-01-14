#ifndef ARM_H
#define ARM_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"


class ArmSub : public Subsystem {
private:
  double offset;

public:
  CANTalon *armMotor;
  ArmSub();
  void InitDefaultCommand();
  void armDown();
  void stop();
  void armUp();
  void readPos();
  void reset();
  void stowArm();
  void setOffset(double offset);
  void disablePositionControl();
};

#endif
