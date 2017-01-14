#include "Shooter.h"
#include "../Commands/ShootDefault.h"
#include "../RobotMap.h"
#include "CANTalon.h"

const int RPM = 7000;

Shooter::Shooter() : Subsystem("Shooter") {
  leftFront = RobotMap::leftFront;
  rightRear = RobotMap::rightRear;
  rightFront = RobotMap::rightFront;
  leftRear = RobotMap::leftRear;

  feeder = RobotMap::feeder;
  feederSensor = RobotMap::feederSensor;

  leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
  rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
  /*

      leftFront->SetControlMode(CANSpeedController::kSpeed);
      leftFront->ConfigNominalOutputVoltage(0.0, 0.0);
      leftFront->ConfigPeakOutputVoltage(12.0, -12.0);
      leftFront->SetSensorDirection(true);
      leftFront->SetP(0.05);
      leftFront->SetI(0.0);
      leftFront->SetD(0.0);
      leftFront->SetF(0.03);


      rightFront->SetControlMode(CANSpeedController::kSpeed);
      rightFront->ConfigNominalOutputVoltage(0.0, 0.0);
      rightFront->ConfigPeakOutputVoltage(12.0, -12.0);
      rightFront->SetSensorDirection(true);
      rightFront->SetP(0.05);
      rightFront->SetI(0.0);
      rightFront->SetD(0.0);
      rightFront->SetF(0.03);
  */
}

void Shooter::InitDefaultCommand() { SetDefaultCommand(new ShootDefault()); }
void Shooter::shootFront() {

  leftFront->Set(1);
  rightFront->Set(-1);
  /*
      leftFront->SetControlMode(CANSpeedController::kSpeed);
      leftFront->Set(RPM);
      rightFront->SetControlMode(CANSpeedController::kSpeed);
      rightFront->Set(-RPM);
  */
}

void Shooter::shootBack() {
  leftRear->Set(-1);
  rightRear->Set(1);
}

void Shooter::stopFront() {
  leftFront->SetControlMode(CANSpeedController::kPercentVbus);
  leftFront->Set(0);
  rightFront->SetControlMode(CANSpeedController::kPercentVbus);
  rightFront->Set(0);
}

void Shooter::stopBack() {
  rightRear->Set(0);
  leftRear->Set(0);
}

void Shooter::feed() { feeder->Set(-0.7); }

void Shooter::deFeed() { feeder->Set(0.5); }

void Shooter::stopFeed() { feeder->Set(0); }

void Shooter::shootDefault(float right, float left) {
  if (right > 0.1) {
    shootFront();
    shootBack();
  } else {
    stopFront();
    stopBack();
  }

  if ((left > 0.1 && feederSensor->GetAverageVoltage() > 4.0) ||
      (left > 0.1 && right > 0.1)) {
    feed();
  } else {
    stopFeed();
  }
}

double Shooter::getVelocity() { return leftFront->GetSpeed(); }
