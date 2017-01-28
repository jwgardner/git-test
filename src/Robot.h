#pragma once

#include <WPILib.h>
#include <Commands/Command.h>
#include <LiveWindow/LiveWindow.h>

#include "Commands/AutonomousCommand.h"
#include "OI.h"
#include "RobotMap.h"
#include "Subsystems/ArmSub.h"
#include "Subsystems/BasicCameraSub.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/GyroSub.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/VisionBridgeSub.h"
#include "Subsystems/WinchSub.h"

class Robot : public IterativeRobot {
public:
	Command *autonomousCommand;
	LiveWindow *lw = LiveWindow::GetInstance();

	static OI *oi;
	static DriveTrain *driveTrain;
	static ArmSub *armSub;
	static GyroSub *gyroSub;
	static Shooter *shooter;
	static std::shared_ptr<BasicCameraSub> basicCameraSub;
	static WinchSub *winchSub;
	static VisionBridgeSub *visionBridge;

	virtual void RobotInit();
	virtual void RobotPeriodic();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

	void ScriptInit();
};
