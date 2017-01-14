#pragma once

#include "WPILib.h"
#include "cscore.h"

class BasicCameraSub : public Subsystem {
public:
  BasicCameraSub(const std::string &cameraName);
  ~BasicCameraSub();

  // Inherited from Subsystem
  virtual void InitDefaultCommand();

  void Disable();
  void Enable();
  bool IsEnabled() const;
  void SendImage();

private:
  bool m_enabled;
  bool m_initialized;
  cs::UsbCamera m_camera;
  llvm::StringRef m_cameraStringRef;

  void _InitializeCamera();
  void _UninitializeCamera();
};
