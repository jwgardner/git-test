#include "BasicCameraSub.h"
#include "Commands/BasicCameraSendCmd.h"
#include "Modules/LCameraServer.h"

BasicCameraSub::BasicCameraSub(const std::string &cameraName)
    : Subsystem("BasicCamera:" + cameraName), m_enabled(false),
      m_initialized(false), m_image(nullptr), m_camera(cameraName, true) {}

BasicCameraSub::~BasicCameraSub() { _UninitializeCamera(); }

void BasicCameraSub::InitDefaultCommand() {
  SetDefaultCommand(new BasicCameraSendCmd(this));
}

void BasicCameraSub::Disable() {
  if (IsEnabled()) {
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

void BasicCameraSub::SendImage() {
  if (IsEnabled()) {
    m_camera.GetImage(m_image);
    LCameraServer::GetInstance()->SetImage(m_image);
  }
}

void BasicCameraSub::_InitializeCamera() {
  if (!m_initialized) {
    m_image = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
    m_camera.SetFPS(10);
    m_camera.SetSize(320, 240);
    m_camera.SetExposureAuto();
    m_camera.SetWhiteBalanceAuto();
    m_camera.SetBrightness(35);
    m_camera.OpenCamera();
    m_camera.StartCapture();
    m_initialized = true;
  }
}

void BasicCameraSub::_UninitializeCamera() {
  if (m_initialized) {
    m_camera.StopCapture();
    m_camera.CloseCamera();
    m_initialized = false;
  }
}
