#pragma once

#include <WPILib.h>
#include <condition_variable>

class VisionSink : public PIDOutput {
public:
  VisionSink();
  virtual ~VisionSink();

  // PIDOutput methods
  void PIDWrite(float output);

  double GetValue();

private:
  std::recursive_mutex _mutex;
  double _value;
};
