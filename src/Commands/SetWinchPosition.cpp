#include "../Robot.h"
#include <Commands/SetWinchPosition.h>

SetWinchPosition::SetWinchPosition(int pos, bool holdPos, double timeout) {
  Requires(Robot::winchSub);
  SetWinchPosition::pos = pos;
  SetWinchPosition::holdPos = holdPos;
  SetTimeout(timeout);
}

// Called just before this Command runs the first time
void SetWinchPosition::Initialize() {
  std::cout << "winch command time start: "
            << DriverStation::GetInstance().GetMatchTime();
  if (Robot::winchSub->angleSensor) {
    if (pos == 0)
      Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch 0", 3.2));
    if (pos == 1)
      Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch 1", 3.0));
    if (pos == 2)
      Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch 2", 3.4));
    if (pos == 3) {
      if (Robot::visionBridge->GetDistance() >
          SmartDashboard::GetNumber("long shot cutoff", 100))
        Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch 0", 3.2));
      else
        Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch 2", 3.4));
    }
  } else {
    if (pos == 0)
      Robot::winchSub->setPos(0.0);
    if (pos == 1)
      Robot::winchSub->setPos(0.1);
    if (pos == 2)
      Robot::winchSub->setPos(0.8);
  }
}

// Called repeatedly when this Command is scheduled to run
void SetWinchPosition::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetWinchPosition::IsFinished() {
  return IsTimedOut() || Robot::winchSub->shooter->OnTarget();
}

// Called once after isFinished returns true
void SetWinchPosition::End() {
  if (!holdPos)
    Robot::winchSub->disablePositionControl();
  std::cout << "winch command time end: "
            << DriverStation::GetInstance().GetMatchTime();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWinchPosition::Interrupted() { End(); }
