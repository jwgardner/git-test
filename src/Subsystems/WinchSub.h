#ifndef WinchSub_H
#define WinchSub_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class WinchSub : public Subsystem {
private:
  CANTalon *motor;
  AnalogInput *shooterSensor;

public:
  bool shooterRaised;
  const static bool angleSensor;
  PIDController *shooter;
  WinchSub();
  void InitDefaultCommand();
  void setPos(double pos);
  void readPos();
  void disablePositionControl();
  void reset();
  void climb();
  void stopClimb();
};

#endif
