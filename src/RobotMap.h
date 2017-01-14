// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "Modules/AnalogChannelVolt.h"
#include "Modules/Logger.h"
#include "Modules/NavX/AHRS.h"
#include "WPILib.h"
#include "CANTalon.h"


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
  static bool SpeedControl;

  static PIDController *driveTrainFrontLeft;
  static CANTalon *driveTrainFrontLeftDrive;
  static AnalogChannelVolt *driveTrainFrontLeftPos;
  static CANTalon *driveTrainFrontLeftSteer;

  static PIDController *driveTrainFrontRight;
  static CANTalon *driveTrainFrontRightDrive;
  static AnalogChannelVolt *driveTrainFrontRightPos;
  static CANTalon *driveTrainFrontRightSteer;

  static PIDController *driveTrainRearLeft;
  static CANTalon *driveTrainRearLeftDrive;
  static AnalogChannelVolt *driveTrainRearLeftPos;
  static CANTalon *driveTrainRearLeftSteer;

  static PIDController *driveTrainRearRight;
  static CANTalon *driveTrainRearRightDrive;
  static AnalogChannelVolt *driveTrainRearRightPos;
  static CANTalon *driveTrainRearRightSteer;

  static I2C *i2c;

  static AHRS *imu;

  static SerialPort *serialPort;

  static CANTalon *leftFront;
  static CANTalon *rightRear;
  static CANTalon *rightFront;
  static CANTalon *leftRear;
  static SpeedController *feeder;
  static AnalogInput *feederSensor;

  static CANTalon *armMotor;

  static CANTalon *winchMotor;
  static AnalogInput *winchPot;
  static PIDController *shooterWinch;

  static void init();
};
#endif