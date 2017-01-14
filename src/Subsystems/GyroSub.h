#ifndef GYROSUB_H
#define GYROSUB_H

#include "../RobotMap.h"
#include "Commands/Subsystem.h"
#include "PIDSource.h"
#include "WPILib.h"
#include "../Robot.h"

//
// The GyroSub subsystem represents the NAV6 accelerometer.
//
// @author JKSalmon
//
class GyroSub : public Subsystem, public PIDSource {
public:
  GyroSub();

  // Subsystem methods
  virtual void InitDefaultCommand();

  // PIDSource methods
  virtual double PIDGet();

  double GetHeading();
  bool IsCalibrating();
  void ResetGyro();

#ifdef USE_NAVX
  float GetDisplacementX();
  float GetDisplacementY();
#endif

private:
// Put everything in private except methods that implement subsystem
// capabilities.
#ifdef USE_NAVX
  KauaiNavX::AHRS *theGyro() { return RobotMap::imu; }
#else
  AHRS *theGyro() { return RobotMap::imu; }
#endif
};

#endif
