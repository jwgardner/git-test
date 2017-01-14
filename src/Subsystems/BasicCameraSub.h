#pragma once

#include "WPILib.h"

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
  Image *m_image;
  USBCamera m_camera;

  void _InitializeCamera();
  void _UninitializeCamera();
};
