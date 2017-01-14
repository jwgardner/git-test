#include "ScriptSleep.h"
#include "../Robot.h"
#include <iostream>

ScriptSleep::ScriptSleep(const char *name, float seconds)
    : Command(name), _seconds(seconds) {
  std::cout << GetName() << "::ctor(" << seconds << ")" << std::endl;
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ScriptSleep::Initialize() {
  std::cout << GetName() << "::Initialize" << std::endl;
  SetTimeout(_seconds);
}

// Called repeatedly when this Command is scheduled to run
void ScriptSleep::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ScriptSleep::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void ScriptSleep::End() { std::cout << GetName() << "::End" << std::endl; }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptSleep::Interrupted() {
  std::cout << GetName() << "::Interrupted" << std::endl;
}
