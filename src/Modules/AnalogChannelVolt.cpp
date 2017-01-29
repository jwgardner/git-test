#include "AnalogChannelVolt.h"
#include "Subsystems/EncoderConstants.h"
#include <math.h>

// ==========================================================================

AnalogChannelVolt::AnalogChannelVolt(uint32_t channel, CANTalon *motor, double offset)
:	AnalogInput(channel) {
	m_motor = motor;
	m_offset = offset;
}

// ==========================================================================

AnalogChannelVolt::AnalogChannelVolt(uint32_t channel, bool inv, int ratio, CANTalon* motor)
:	AnalogInput(channel) {
	// Inv = inv;
	// Ratio = ratio;

	// rev = 5.0;
	// halfrev = rev/Ratio;
	// scale = rev/(4.8-.2);

	// m_channel = channel;
	SetSampleRate(1000);
	/*
	m_trig = new AnalogTrigger(channel);
	m_trig->SetFiltered(true);
	m_trig->SetLimitsVoltage(1.35,3.65);

	m_count = new Counter();
	m_count->SetUpDownCounterMode();
	m_count->SetUpSource(m_trig, AnalogTriggerType::kFallingPulse);
	m_count->SetDownSource(m_trig, AnalogTriggerType::kRisingPulse);
	m_count->SetUpSourceEdge(true,false);
	m_count->SetDownSourceEdge(true,false);
	*/
	m_motor = motor;
	m_offset = 0;
}
/*
float AnalogChannelVolt::GetAverageVoltage()
{
    return GetVoltage();
}
*/
/*
void AnalogChannelVolt::ResetTurns()
{
    //m_count->Reset();
}
*/
/*
void AnalogChannelVolt::Start()
{
    LOG("analogChannelVolt start\r");
}
*/
/*
float AnalogChannelVolt::GetVoltage()
{
  return PIDGet();
}
*/
double AnalogChannelVolt::GetAngle() {
  double position = m_motor->GetPosition() - m_offset;
  position -= trunc(position);
  if (position < 0)
    position++;
  position *= EncoderConstants::FULL_TURN;
  return position;
}

double AnalogChannelVolt::GetRawAngle() { return PIDGet(); }

double AnalogChannelVolt::GetTurns() const {
  return m_motor->GetPosition() - m_offset;
}

void AnalogChannelVolt::SetOffset(double offset) { m_offset = offset; }

double AnalogChannelVolt::PIDGet() {
  double position = m_motor->GetPosition();
  position -= trunc(position);
  if (position < 0)
    position++;
  position *= EncoderConstants::FULL_TURN;
  return position;
}

AnalogChannelVolt::~AnalogChannelVolt() {
  /*
      if(m_trig)
          delete m_trig;
      if(m_count)
          delete m_count;
  */
}
