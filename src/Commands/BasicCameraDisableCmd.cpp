#include "BasicCameraDisableCmd.h"

// ==========================================================================

BasicCameraDisableCmd::BasicCameraDisableCmd(
    std::shared_ptr<BasicCameraSub> camera)
    : Command("BasicCamera Send"), m_camera(camera) {
  Requires(camera.get());
  SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void BasicCameraDisableCmd::Initialize() {}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void BasicCameraDisableCmd::Execute() { m_camera->Disable(); }

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool BasicCameraDisableCmd::IsFinished() { return true; }

// ==========================================================================
// Called once after isFinished returns true

void BasicCameraDisableCmd::End() {}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void BasicCameraDisableCmd::Interrupted() { End(); }

// ==========================================================================
