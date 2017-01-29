#pragma once

#include <Commands/Subsystem.h>

// ==========================================================================

class BasicCameraSub : public frc::Subsystem {
public:
	BasicCameraSub(const std::string& cameraName);
	~BasicCameraSub();

	void Enable();
	bool IsEnabled() const;

private:
	bool m_enabled;

	void _InitializeCamera();
};

// ==========================================================================
