#pragma once

#include "Commands/Subsystem.h"
#include "Timer.h"
#include "WPILib.h"
#include "CANTalon.h"

class Shooter : public Subsystem {
private:
  SpeedController *feeder;

public:
  CANTalon *leftFront;
  CANTalon *rightRear;
  CANTalon *rightFront;
  CANTalon *leftRear;
  AnalogInput *feederSensor;
  Shooter();
  void InitDefaultCommand();
  void shootFront();
  void shootBack();
  void stopFront();
  void stopBack();
  void feed();
  void deFeed();
  void stopFeed();
  void shootDefault(float right, float left);
  double getVelocity();
};


