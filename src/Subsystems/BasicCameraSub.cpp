#include "BasicCameraSub.h"
#include "Commands/BasicCameraSendCmd.h"
#include "CameraServer.h"

BasicCameraSub::BasicCameraSub(const std::string &cameraName)
    : Subsystem("BasicCamera:" + cameraName), m_enabled(false) {}


void BasicCameraSub::Enable() {
  if (!IsEnabled()) {
    _InitializeCamera();
    m_enabled = true;
  }
}

bool BasicCameraSub::IsEnabled() const { return m_enabled; }

void BasicCameraSub::_InitializeCamera() {
	CameraServer::GetInstance()->StartAutomaticCapture();
}
