#ifndef _ROBOT_H
#define _ROBOT_H

#include "Commands/AutonomousCommand.h"
#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "OI.h"
#include "RobotMap.h"
#include "Subsystems/ArmSub.h"
#include "Subsystems/BasicCameraSub.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/GyroSub.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/VisionBridgeSub.h"
#include "Subsystems/WinchSub.h"
#include "WPILib.h"

class Robot : public IterativeRobot {
public:
  Command *autonomousCommand;
  static OI *oi;
  static DriveTrain *driveTrain;
  static ArmSub *armSub;
  static GyroSub *gyroSub;
  static Shooter *shooter;
  static std::shared_ptr<BasicCameraSub> basicCameraSub;
  static WinchSub *winchSub;
  static VisionBridgeSub *visionBridge;
  LiveWindow *lw = LiveWindow::GetInstance();

  virtual void RobotInit();
  virtual void DisabledInit();
  virtual void DisabledPeriodic();
  virtual void AutonomousInit();
  virtual void AutonomousPeriodic();
  virtual void TeleopInit();
  virtual void TeleopPeriodic();
  virtual void TestPeriodic();
  void ScriptInit();
  // void cameraInit();
};
#endif
