#pragma once

#include <WPILib.h>

class VisionSource : public PIDSource {
public:
  VisionSource();
  virtual ~VisionSource();

  // PIDSource methods
  double PIDGet();
};
