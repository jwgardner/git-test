#pragma once

#include "Subsystems/BasicCameraSub.h"
#include <Commands/Command.h>

class BasicCameraSendCmd : public Command {
public:
  BasicCameraSendCmd(BasicCameraSub *camera);

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

private:
  BasicCameraSub *m_camera;
};
