#pragma once

#include "Subsystems/BasicCameraSub.h"
#include <Commands/Command.h>

class BasicCameraEnableCmd : public Command {
public:
  BasicCameraEnableCmd(std::shared_ptr<BasicCameraSub> camera);

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

private:
  std::shared_ptr<BasicCameraSub> m_camera;
};
