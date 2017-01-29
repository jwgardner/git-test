#pragma once

#include "Modules/Logger.h"
#include <AnalogInput.h>
#include <AnalogTrigger.h>
#include <AnalogTriggerOutput.h>
#include <Base.h>
#include <Counter.h>
#include <WPILib.h>
#include <CANTalon.h>

// ==========================================================================
// TODO - Clean up this class

class AnalogChannelVolt : public AnalogInput {
public:
  AnalogChannelVolt(uint32_t channel, CANTalon *motor, double offset);
  AnalogChannelVolt(uint32_t channel, bool inv, int ratio, CANTalon *motor);
  virtual ~AnalogChannelVolt();
  double PIDGet() override;
  // float GetAverageVoltage();
  // float GetVoltage();
  // void ResetTurns();
  // void Start();
  double GetAngle();
  double GetRawAngle();
  double GetTurns() const;
  void SetOffset(double offset);

private:
  CANTalon* m_motor;
  double m_offset;
  // AnalogTrigger* m_trig;
  // Counter* m_count;
  // uint32_t m_channel;
  // bool Inv;
  // float rev;
  // float halfrev;
  // float scale;
  // int Ratio;
};

// ==========================================================================
