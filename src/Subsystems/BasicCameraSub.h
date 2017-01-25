#pragma once

#include "WPILib.h"
#include "cscore.h"

class BasicCameraSub : public Subsystem {
public:

  BasicCameraSub(const std::string &cameraName);
  ~BasicCameraSub() {};

  void Enable();
  bool IsEnabled() const;

private:
  bool m_enabled;

  void _InitializeCamera();
};
