#include "BasicCameraSub.h"
#include "Commands/BasicCameraSendCmd.h"
#include "CameraServer.h"

BasicCameraSub::BasicCameraSub(const std::string &cameraName)
    : Subsystem("BasicCamera:" + cameraName), m_enabled(false),
      m_initialized(false), m_camera(cameraName, true), m_cameraStringRef(cameraName) {}

BasicCameraSub::~BasicCameraSub() { _UninitializeCamera(); }

void BasicCameraSub::InitDefaultCommand() {
  SetDefaultCommand(new BasicCameraSendCmd(this));
}

void BasicCameraSub::Disable() {
  if (IsEnabled()) {
	_UninitializeCamera();
    m_enabled = false;
  }
}

void BasicCameraSub::Enable() {
  if (!IsEnabled()) {
    _InitializeCamera();
    m_enabled = true;
  }
}

bool BasicCameraSub::IsEnabled() const { return m_enabled; }

void BasicCameraSub::_InitializeCamera() {
  if (!m_initialized) {
	CameraServer *serverReference = CameraServer::GetInstance();
	m_camera = serverReference->StartAutomaticCapture(m_cameraStringRef, 0);
    m_camera.SetFPS(10);
    m_camera.SetResolution(320, 240);
    m_camera.SetExposureAuto();
    m_camera.SetWhiteBalanceAuto();
    m_camera.SetBrightness(35);
    m_initialized = true;
  }
}

void BasicCameraSub::_UninitializeCamera() {
  if (m_initialized) {
	CameraServer *serverReference = CameraServer::GetInstance();
	serverReference->RemoveCamera(m_cameraStringRef);
  }
}
