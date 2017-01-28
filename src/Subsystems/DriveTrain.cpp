#include "Subsystems/DriveTrain.h"
#include "Commands/CrabDrive.h"
#include "Commands/PositionDrive.h"
#include "Modules/Constants.h"
#include "Modules/Logger.h"
#include "Robot.h"
#include "RobotMap.h"
#include "Subsystems/EncoderConstants.h"

#ifdef TESTSWERVE
#define MAXTURNS 3
#else
#define MAXTURNS 3
#define SOFTTURNLIMIT 2
#endif

const float TWISTSCALE = 0.6;

const float DEAD_ZONE = 0.1;

const float driveScale = 950;
// const double AVERAGE_VOLTAGE_BASE = EncoderConstants::HALF_TURN;

//#define GYROP  .05
#define GYROP .01
#define GYROMAX .5

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  LOG("DriveTrain::DriveTrain");

  frontLeft = RobotMap::driveTrainFrontLeft;
  frontLeftDrive = RobotMap::driveTrainFrontLeftDrive;
  frontLeftPos = RobotMap::driveTrainFrontLeftPos;
  frontLeftSteer = RobotMap::driveTrainFrontLeftSteer;

  frontRight = RobotMap::driveTrainFrontRight;
  frontRightDrive = RobotMap::driveTrainFrontRightDrive;
  frontRightPos = RobotMap::driveTrainFrontRightPos;
  frontRightSteer = RobotMap::driveTrainFrontRightSteer;

  rearLeft = RobotMap::driveTrainRearLeft;
  rearLeftDrive = RobotMap::driveTrainRearLeftDrive;
  rearLeftPos = RobotMap::driveTrainRearLeftPos;
  rearLeftSteer = RobotMap::driveTrainRearLeftSteer;

  rearRight = RobotMap::driveTrainRearRight;
  rearRightDrive = RobotMap::driveTrainRearRightDrive;
  rearRightPos = RobotMap::driveTrainRearRightPos;
  rearRightSteer = RobotMap::driveTrainRearRightSteer;

  lastx = 0.0;
  lasty = 0.0;
  lasttwist = 0.0;

  FLInv = 1;
  FRInv = 1;
  RRInv = 1;
  RLInv = 1;
  DriveBackFlag = false;
  robotangle = 0;
  unwinding = false;

  FLValue = 0;
  FRValue = 0;
  RLValue = 0;
  RRValue = 0;
}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CrabDrive());
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::SetWheelbase(float w, float x, float y) {
  W = w;
  X = x;
  Y = y;
}
void DriveTrain::SetOffsets(double FLOff, double FROff, double RLOff,
                            double RROff) {
  FLOffset = FLOff;
  FROffset = FROff;
  RLOffset = RLOff;
  RROffset = RROff;
}
/*
bool DriveTrain::unwindwheel(AnalogChannelVolt * wheel, PIDController * pid,
double offset, bool output){
    double temp;
    offset /= EncoderConstants::FULL_TURN;
    double turns = wheel->GetTurns() - offset;
    if (output) SmartDashboard::PutNumber("offset", offset);
    if (output) SmartDashboard::PutNumber("turns", turns);
    if (output) SmartDashboard::PutNumber("curr", wheel->GetAngle());
    if(turns >= 0.1) {
        temp = wheel->GetAngle() - 0.75;
        if(temp < 0.0) temp += EncoderConstants::FULL_TURN;
        pid->SetSetpoint(temp);
        if (output) SmartDashboard::PutNumber("temp", temp);
        return true;
    } else
    if(turns <= -0.1) {
        temp = wheel->GetAngle() + 0.75;
        if(temp > EncoderConstants::FULL_TURN) temp -=
EncoderConstants::FULL_TURN;
        pid->SetSetpoint(temp);
        if (output) SmartDashboard::PutNumber("temp", temp);
        return true;
    } else return false;
}
*/
bool DriveTrain::unwind() { // float y, float x){
  // Dashboard();
  frontLeft->Disable();
  frontRight->Disable();
  rearLeft->Disable();
  rearRight->Disable();

  frontLeftSteer->SetControlMode(CANSpeedController::kPosition);
  frontRightSteer->SetControlMode(CANSpeedController::kPosition);
  rearLeftSteer->SetControlMode(CANSpeedController::kPosition);
  rearRightSteer->SetControlMode(CANSpeedController::kPosition);

  frontLeftSteer->SetP(0.4);
  frontRightSteer->SetP(0.4);
  rearLeftSteer->SetP(0.4);
  rearRightSteer->SetP(0.4);

  frontLeftSteer->ConfigPeakOutputVoltage(6.0, -6.0);
  frontRightSteer->ConfigPeakOutputVoltage(6.0, -6.0);
  rearLeftSteer->ConfigPeakOutputVoltage(6.0, -6.0);
  rearRightSteer->ConfigPeakOutputVoltage(6.0, -6.0);

  frontLeftSteer->Set(FLOffset / EncoderConstants::FULL_TURN);
  frontRightSteer->Set(FROffset / EncoderConstants::FULL_TURN);
  rearLeftSteer->Set(RLOffset / EncoderConstants::FULL_TURN);
  rearRightSteer->Set(RROffset / EncoderConstants::FULL_TURN);

  bool retval = true;
  unwinding = true;
  robotangle = 0;
  // if(!(unwindwheel(frontLeftPos, frontLeft, FLOffset, false) ||
  // unwindwheel(frontRightPos, frontRight, FROffset, false) ||
  //        unwindwheel(rearLeftPos, rearLeft, RLOffset, true) ||
  //        unwindwheel(rearRightPos, rearRight, RROffset, false)))
  /*{
      unwinding = 0;
      retval = 0;
  }
   */
  return retval;
}

void DriveTrain::doneunwind() { unwinding = 0; }

void DriveTrain::PositionModeTwist(float desiredangle) {
  frontLeft->SetSetpoint(CorrectSteerSetpoint(FLOffset + 0.625));
  frontRight->SetSetpoint(CorrectSteerSetpoint(FROffset - 0.625));
  rearLeft->SetSetpoint(CorrectSteerSetpoint(RLOffset - 0.625));
  rearRight->SetSetpoint(CorrectSteerSetpoint(RROffset + 0.625));
}

// keeps controls consistent regardless of rotation of robot
void DriveTrain::FieldCentricCrab(float twist, float y, float x,
                                  bool operatorControl) {
  float FWD = y;
  float STR = x;

  robotangle = (Robot::gyroSub->PIDGet()) * pi / 180;

  FWD = y * cos(robotangle) + x * sin(robotangle);
  STR = -y * sin(robotangle) + x * cos(robotangle);

  Crab(twist, FWD, STR, operatorControl);
}

// attempts to keep robot square to the field as it drives
void DriveTrain::GyroCrab(float desiredangle, float y, float x,
                          bool operatorControl) {
  robotangle = Robot::gyroSub->PIDGet();
  // std::cout << "robotangle " << robotangle << std::endl;

  float twist = desiredangle - robotangle;
  while (twist > 180.0)
    twist -= 360.0;
  while (twist < -180.0)
    twist += 360.0;

  twist = std::min(GYROMAX, std::max(-GYROMAX, twist * GYROP));
  // std::cout << "twist " << twist << std::endl;
  Crab(twist, y, x, operatorControl);
}

void DriveTrain::Crab(float twist, float y, float x, bool operatorControl) {
  // Dashboard();
  // enableSpeedControl();

  // stop PID loop if wires wrap.
  if (unwinding || abs(frontRightPos->GetTurns()) > MAXTURNS ||
      abs(rearRightPos->GetTurns()) > MAXTURNS ||
      abs(frontLeftPos->GetTurns()) > MAXTURNS ||
      abs(rearLeftPos->GetTurns()) > MAXTURNS) {
    SetDriveSpeed(0, 0, 0, 0);
    return;
  }

  // this stores the direction of joystick when all axis last crossed into the
  // deadzone
  // and keeps the wheels pointed that direction
  // this .1 should be kept the same as the deadzone in oi.cpp
  if (operatorControl && x == 0.0 && y == 0.0 && twist == 0.0) {
    if (fabs(lasty) > DEAD_ZONE || fabs(lastx) > DEAD_ZONE ||
        fabs(lasttwist) > DEAD_ZONE) {
      y = std::min(std::max(lasty, -DEAD_ZONE), DEAD_ZONE);
      x = std::min(std::max(lastx, -DEAD_ZONE), DEAD_ZONE);
      twist = std::min(std::max(lasttwist, -DEAD_ZONE), DEAD_ZONE);
    } else {
      y = .05;
      // default wheel position
    }
  } else if (Robot::oi->GetButtonA() && !operatorControl && twist == 0.0) {
    twist = 0.05;
  }

  lastx = x;
  lasty = y;
  lasttwist = twist;

  if (operatorControl) {
    // scale for operator control
    x *= 1;
    y *= 1;
    float avg = (std::abs(x) + std::abs(y)) / 2;
    float scale = 1 - avg / 2;
    twist *= scale; // TWISTSCALE;
  }

  float FWD = y;
  float STR = x;

  //    FWD = y*cos(robotangle) + x*sin(robotangle);
  //    STR = -y*sin(robotangle) + x*cos(robotangle);

  //    radius = sqrt(pow(2*Y,2)+pow(X,2));
  radius = sqrt(pow(Y, 2) + pow(X, 2));

  AP = STR - twist * X / radius;
  BP = STR + twist * X / radius;
  //    CP = FWD - twist*2*Y/radius;
  //    DP = FWD + twist*2*Y/radius;
  CP = FWD - twist * Y / radius;
  DP = FWD + twist * Y / radius;

  float FLSetPoint = EncoderConstants::HALF_TURN;
  float FRSetPoint = EncoderConstants::HALF_TURN;
  float RLSetPoint = EncoderConstants::HALF_TURN;
  float RRSetPoint = EncoderConstants::HALF_TURN;

  if (DP != 0 || BP != 0)
    FLSetPoint = (EncoderConstants::HALF_TURN +
                  EncoderConstants::HALF_TURN / pi * atan2(BP, DP));
  if (BP != 0 || CP != 0)
    FRSetPoint = (EncoderConstants::HALF_TURN +
                  EncoderConstants::HALF_TURN / pi * atan2(BP, CP));
  if (AP != 0 || DP != 0)
    RLSetPoint = (EncoderConstants::HALF_TURN +
                  EncoderConstants::HALF_TURN / pi * atan2(AP, DP));
  if (AP != 0 || CP != 0)
    RRSetPoint = (EncoderConstants::HALF_TURN +
                  EncoderConstants::HALF_TURN / pi * atan2(AP, CP));

  SetSteerSetpoint(FLSetPoint, FRSetPoint, RLSetPoint, RRSetPoint);

  FL = sqrt(pow(BP, 2) + pow(DP, 2));
  FR = sqrt(pow(BP, 2) + pow(CP, 2));
  RL = sqrt(pow(AP, 2) + pow(DP, 2));
  RR = sqrt(pow(AP, 2) + pow(CP, 2));

  // Solve for fastest wheel speed
  double speedarray[] = {fabs(FL), fabs(FR), fabs(RL), fabs(RR)};

  int length = 4;
  double maxspeed = speedarray[0];
  for (int i = 1; i < length; i++) {
    if (speedarray[i] > maxspeed)
      maxspeed = speedarray[i];
  }

  // Set ratios based on maximum wheel speed
  if (maxspeed > 1 || maxspeed < -1) {
    FLRatio = FL / maxspeed;
    FRRatio = FR / maxspeed;
    RLRatio = RL / maxspeed;
    RRRatio = RR / maxspeed;
  } else {
    FLRatio = FL;
    FRRatio = FR;
    RLRatio = RL;
    RRRatio = RR;
  }
  // if(y > 0.049 && y < .051)

  if (operatorControl && fabs(x) <= DEAD_ZONE && fabs(y) <= DEAD_ZONE &&
      fabs(twist) <= DEAD_ZONE) {
    FLRatio = 0.0;
    FRRatio = 0.0;
    RLRatio = 0.0;
    RRRatio = 0.0;
  }

  // Set drive speeds
  SetDriveSpeed(FLRatio, -FRRatio, RLRatio, -RRRatio);
}

double DriveTrain::CorrectSteerSetpoint(double setpoint) {
  if (setpoint < 0) {
    return setpoint + EncoderConstants::FULL_TURN;
  } else if (setpoint > EncoderConstants::FULL_TURN) {
    return setpoint - EncoderConstants::FULL_TURN;
  } else if (setpoint == EncoderConstants::FULL_TURN) {
    return 0;
  } else {
    return setpoint;
  }
}

void DriveTrain::SetSteerSetpoint(float FLSetPoint, float FRSetPoint,
                                  float RLSetPoint, float RRSetPoint) {
  //////////////////////////////////
  // Front Left Wheel
  //////////////////////////////////
  if (frontLeftPos->GetTurns() > SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(FLSetPoint + FLOffset - frontLeftPos->GetAngle()) >
        EncoderConstants::HALF_TURN) {
      frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset));
      FLInv = 1;
    } else {
      frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset -
                                                  EncoderConstants::HALF_TURN));
      FLInv = -1;
    }
  } else if (frontLeftPos->GetTurns() < -SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(FLSetPoint + FLOffset - frontLeftPos->GetAngle()) <
        EncoderConstants::HALF_TURN) {
      frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset));
      FLInv = 1;
    } else {
      frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset -
                                                  EncoderConstants::HALF_TURN));
      FLInv = -1;
    }
  } else {
    // Default rotation logic
    if (fabs(FLSetPoint + FLOffset - frontLeftPos->GetAngle()) <
            EncoderConstants::QUARTER_TURN ||
        fabs(FLSetPoint + FLOffset - frontLeftPos->GetAngle()) >
            EncoderConstants::THREEQUARTER_TURN) {
      frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset));
      FLInv = 1;
    } else {
      frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset -
                                                  EncoderConstants::HALF_TURN));
      FLInv = -1;
    }
  }
  //////////////////////////////////
  // Front Right Wheel
  //////////////////////////////////
  if (frontRightPos->GetTurns() > SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(FRSetPoint + FROffset -
                             frontRightPos->GetAngle()) >
        EncoderConstants::HALF_TURN) {
      frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset));
      FRInv = 1;
    } else {
      frontRight->SetSetpoint(CorrectSteerSetpoint(
          FRSetPoint + FROffset - EncoderConstants::HALF_TURN));
      FRInv = -1;
    }
  } else if (frontRightPos->GetTurns() < -SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(FRSetPoint + FROffset -
                             frontRightPos->GetAngle()) <
        EncoderConstants::HALF_TURN) {
      frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset));
      FRInv = 1;
    } else {
      frontRight->SetSetpoint(CorrectSteerSetpoint(
          FRSetPoint + FROffset - EncoderConstants::HALF_TURN));
      FRInv = -1;
    }
  } else {
    // default rotation logic
    if (fabs(FRSetPoint + FROffset - frontRightPos->GetAngle()) <
            EncoderConstants::QUARTER_TURN ||
        fabs(FRSetPoint + FROffset - frontRightPos->GetAngle()) >
            EncoderConstants::THREEQUARTER_TURN) {
      frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset));
      FRInv = 1;
    } else {
      frontRight->SetSetpoint(CorrectSteerSetpoint(
          FRSetPoint + FROffset - EncoderConstants::HALF_TURN));
      FRInv = -1;
    }
  }
  //////////////////////////////////
  // Rear Left Wheel
  //////////////////////////////////
  if (rearLeftPos->GetTurns() > SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(RLSetPoint + RLOffset - rearLeftPos->GetAngle()) >
        EncoderConstants::HALF_TURN) {
      rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset));
      RLInv = 1;
    } else {
      rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset -
                                                 EncoderConstants::HALF_TURN));
      RLInv = -1;
    }
  } else if (rearLeftPos->GetTurns() < -SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(RLSetPoint + RLOffset - rearLeftPos->GetAngle()) <
        EncoderConstants::HALF_TURN) {
      rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset));
      RLInv = 1;
    } else {
      rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset -
                                                 EncoderConstants::HALF_TURN));
      RLInv = -1;
    }
  } else {
    // default rotation logic
    if (fabs(RLSetPoint + RLOffset - rearLeftPos->GetAngle()) <
            EncoderConstants::QUARTER_TURN ||
        fabs(RLSetPoint + RLOffset - rearLeftPos->GetAngle()) >
            EncoderConstants::THREEQUARTER_TURN) {
      rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset));
      RLInv = 1;
    } else {
      rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset -
                                                 EncoderConstants::HALF_TURN));
      RLInv = -1;
    }
  }
  //////////////////////////////////
  // Rear Right Wheel
  //////////////////////////////////
  if (rearRightPos->GetTurns() > SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(RRSetPoint + RROffset - rearRightPos->GetAngle()) >
        EncoderConstants::HALF_TURN) {
      rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset));
      RRInv = 1;
    } else {
      rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset -
                                                  EncoderConstants::HALF_TURN));
      RRInv = -1;
    }
  } else if (rearRightPos->GetTurns() < -SOFTTURNLIMIT) {
    if (CorrectSteerSetpoint(RRSetPoint + RROffset - rearRightPos->GetAngle()) <
        EncoderConstants::HALF_TURN) {
      rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset));
      RRInv = 1;
    } else {
      rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset -
                                                  EncoderConstants::HALF_TURN));
      RRInv = -1;
    }
  } else {
    // default rotation logic
    if (fabs(RRSetPoint + RROffset - rearRightPos->GetAngle()) <
            EncoderConstants::QUARTER_TURN ||
        fabs(RRSetPoint + RROffset - rearRightPos->GetAngle()) >
            EncoderConstants::THREEQUARTER_TURN) {
      rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset));
      RRInv = 1;
    } else {
      rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset -
                                                  EncoderConstants::HALF_TURN));
      RRInv = -1;
    }
  }
}

void DriveTrain::SetDriveSpeed(float FLSpeed, float FRSpeed, float RLSpeed,
                               float RRSpeed) {
  if (RobotMap::SpeedControl) {
    frontLeftDrive->Set(FLSpeed * FLInv * driveScale);
    frontRightDrive->Set(FRSpeed * FRInv * driveScale);
    rearLeftDrive->Set(RLSpeed * RLInv * driveScale);
    rearRightDrive->Set(RRSpeed * RRInv * driveScale);
  } else {
    frontLeftDrive->Set(FLSpeed * FLInv);
    frontRightDrive->Set(FRSpeed * FRInv);
    rearLeftDrive->Set(RLSpeed * RLInv);
    rearRightDrive->Set(RRSpeed * RRInv);
  }
}

void DriveTrain::Lock() {
  SetSteerSetpoint(3.0, 1.5, 3.0, 1.5);
  SetDriveSpeed(0, 0, 0, 0);
}

void DriveTrain::SideLock() {
  SetSteerSetpoint(2.0, 0.75, 3.25, 4.5);
  SetDriveSpeed(0, 0, 0, 0);
}

bool DriveTrain::GetDriveBackFlag() { return DriveBackFlag; }

void DriveTrain::SetDriveBackFlag(bool flag) { DriveBackFlag = flag; }

void DriveTrain::updateDistanceEncoders() {
  FLValue = frontLeftDrive->GetPosition();
  FRValue = frontRightDrive->GetPosition();
  RLValue = rearLeftDrive->GetPosition();
  RRValue = rearRightDrive->GetPosition();
}

double DriveTrain::getDistanceEncodersValues() {
  double average = (FLValue + FRValue + RLValue + RRValue) / 4;
  return average;
}

void DriveTrain::zeroDistanceEncoders() {
  frontLeftDrive->SetPosition(0);
  frontRightDrive->SetPosition(0);
  rearLeftDrive->SetPosition(0);
  rearRightDrive->SetPosition(0);
}

void DriveTrain::zeroSteeringEncoders() {
  frontLeftSteer->SetPosition(0);
  frontRightSteer->SetPosition(0);
  rearLeftSteer->SetPosition(0);
  rearRightSteer->SetPosition(0);
}

void DriveTrain::setWheelOffsets() {
  // Get the current steering positions from the drive train.
  auto FLPosition = Robot::driveTrain->frontLeftPos->GetRawAngle();
  auto FRPosition = Robot::driveTrain->frontRightPos->GetRawAngle();
  auto RLPosition = Robot::driveTrain->rearLeftPos->GetRawAngle();
  auto RRPosition = Robot::driveTrain->rearRightPos->GetRawAngle();
  auto ArmPosition = Robot::armSub->armMotor->GetPosition();

  LogSettings(FLPosition, FRPosition, RLPosition, RRPosition);

  // Save the positions to Preferences.
  auto prefs = Preferences::GetInstance();
  prefs->PutDouble(Constants::FL_POS_NAME, FLPosition);
  prefs->PutDouble(Constants::FR_POS_NAME, FRPosition);
  prefs->PutDouble(Constants::RL_POS_NAME, RLPosition);
  prefs->PutDouble(Constants::RR_POS_NAME, RRPosition);
  prefs->PutDouble(Constants::ARM_POSITION_NAME, ArmPosition);

  //prefs->Save();

  // Set the drive train positions.
  SetOffsets(FLPosition, FRPosition, RLPosition, RRPosition);
  Robot::armSub->setOffset(ArmPosition);
}

void DriveTrain::loadWheelOffsets() {
  LOG("DriveTrainSettings::LoadSettings");

  // Load the positions from Preferences.
  auto prefs = Preferences::GetInstance();
  auto FLPosition =
      prefs->GetDouble(Constants::FL_POS_NAME, Constants::FL_POS_DEFAULT);
  auto FRPosition =
      prefs->GetDouble(Constants::FR_POS_NAME, Constants::FR_POS_DEFAULT);
  auto RLPosition =
      prefs->GetDouble(Constants::RL_POS_NAME, Constants::RL_POS_DEFAULT);
  auto RRPosition =
      prefs->GetDouble(Constants::RR_POS_NAME, Constants::RR_POS_DEFAULT);
  auto ArmPosition = prefs->GetDouble(Constants::ARM_POSITION_NAME,
                                      Constants::ARM_POSITION_DEFAULT);

  LogSettings(FLPosition, FRPosition, RLPosition, RRPosition);

  // Set the drive train positions.
  SetOffsets(FLPosition, FRPosition, RLPosition, RRPosition);
  Robot::armSub->setOffset(ArmPosition);
}

void DriveTrain::LogSettings(double fl, double fr, double rl, double rr) {
  char sz[256];
  sprintf(sz, "Wheel Positions: FL %f, FR %f, RL %f, RR %f", fl, fr, rl, rr);
  LOG(sz);
}

void DriveTrain::Dashboard() {
  SmartDashboard::PutNumber("Steering Motor Encoder FR",
                            frontRightPos->PIDGet());
  SmartDashboard::PutNumber("Steering Motor Encoder FL",
                            frontLeftPos->PIDGet());
  SmartDashboard::PutNumber("Steering Motor Encoder RR",
                            rearRightPos->PIDGet());
  SmartDashboard::PutNumber("Steering Motor Encoder RL", rearLeftPos->PIDGet());

  SmartDashboard::PutNumber("Steering Motor Turns FR",
                            frontRightSteer->GetPosition() -
                                FROffset / EncoderConstants::FULL_TURN); // /5.0
  SmartDashboard::PutNumber("Steering Motor Turns FL",
                            frontLeftSteer->GetPosition() -
                                FLOffset / EncoderConstants::FULL_TURN); // /5.0
  SmartDashboard::PutNumber("Steering Motor Turns RR",
                            rearRightSteer->GetPosition() -
                                RROffset / EncoderConstants::FULL_TURN); // /5.0
  SmartDashboard::PutNumber("Steering Motor Turns RL",
                            rearLeftSteer->GetPosition() -
                                RLOffset / EncoderConstants::FULL_TURN); // /5.0

  SmartDashboard::PutNumber("FL Setpoint", frontLeft->GetSetpoint());
  SmartDashboard::PutNumber("FR Setpoint", frontRight->GetSetpoint());
  SmartDashboard::PutNumber("RL Setpoint", rearLeft->GetSetpoint());
  SmartDashboard::PutNumber("RR Setpoint", rearRight->GetSetpoint());
}

void DriveTrain::CrabInit() {
  frontLeft->Enable();
  frontRight->Enable();
  rearLeft->Enable();
  rearRight->Enable();
  frontLeftSteer->SetControlMode(CANSpeedController::kPercentVbus);
  frontRightSteer->SetControlMode(CANSpeedController::kPercentVbus);
  rearLeftSteer->SetControlMode(CANSpeedController::kPercentVbus);
  rearRightSteer->SetControlMode(CANSpeedController::kPercentVbus);
}

void DriveTrain::SetWheelsStraight() {
  frontLeft->SetSetpoint(FLOffset);
  frontRight->SetSetpoint(FROffset);
  rearLeft->SetSetpoint(RLOffset);
  rearRight->SetSetpoint(RROffset);
}

void DriveTrain::ArcadeDriveMode(float x, float y) {
  float leftMotorOutput;
  float rightMotorOutput;

  if (y > 0.0) {
    if (x > 0.0) {
      leftMotorOutput = y - x;
      rightMotorOutput = std::max(y, x);
    } else {
      leftMotorOutput = std::max(y, -x);
      rightMotorOutput = y + x;
    }
  } else {
    if (x > 0.0) {
      leftMotorOutput = -std::max(-y, x);
      rightMotorOutput = y + x;
    } else {
      leftMotorOutput = y - x;
      rightMotorOutput = -std::max(-y, -x);
    }
  }

  SetDriveSpeed(leftMotorOutput, rightMotorOutput, leftMotorOutput,
                rightMotorOutput);
}

void DriveTrain::disableSpeedControl() {
  frontLeftDrive->SetControlMode(CANSpeedController::kPercentVbus);
  frontRightDrive->SetControlMode(CANSpeedController::kPercentVbus);
  rearLeftDrive->SetControlMode(CANSpeedController::kPercentVbus);
  rearRightDrive->SetControlMode(CANSpeedController::kPercentVbus);
  RobotMap::SpeedControl = 0;
}

void DriveTrain::enableSpeedControl() {
  frontLeftDrive->SelectProfileSlot(0);
  frontRightDrive->SelectProfileSlot(0);
  rearLeftDrive->SelectProfileSlot(0);
  rearRightDrive->SelectProfileSlot(0);
  frontLeftDrive->ConfigPeakOutputVoltage(12.0, -12.0);
  frontRightDrive->ConfigPeakOutputVoltage(12.0, -12.0);
  rearLeftDrive->ConfigPeakOutputVoltage(12.0, -12.0);
  rearRightDrive->ConfigPeakOutputVoltage(12.0, -12.0);
  frontLeftDrive->SetControlMode(CANSpeedController::kSpeed);
  frontRightDrive->SetControlMode(CANSpeedController::kSpeed);
  rearLeftDrive->SetControlMode(CANSpeedController::kSpeed);
  rearRightDrive->SetControlMode(CANSpeedController::kSpeed);
  RobotMap::SpeedControl = 1;
}

void DriveTrain::enablePositionControl() {
  frontLeftDrive->SelectProfileSlot(1);
  frontRightDrive->SelectProfileSlot(1);
  rearLeftDrive->SelectProfileSlot(1);
  rearRightDrive->SelectProfileSlot(1);
  frontLeftDrive->ConfigPeakOutputVoltage(4.0, -4.0);
  frontRightDrive->ConfigPeakOutputVoltage(4.0, -4.0);
  rearLeftDrive->ConfigPeakOutputVoltage(4.0, -4.0);
  rearRightDrive->ConfigPeakOutputVoltage(4.0, -4.0);
  frontLeftDrive->SetControlMode(CANSpeedController::kPosition);
  frontRightDrive->SetControlMode(CANSpeedController::kPosition);
  rearLeftDrive->SetControlMode(CANSpeedController::kPosition);
  rearRightDrive->SetControlMode(CANSpeedController::kPosition);
  RobotMap::SpeedControl = 2;
}

void DriveTrain::enableSteeringPID() {
  /*
  if (FLOffset > 2.5) frontLeft->SetSetpoint(FLOffset - 2.5);
  else frontLeft->SetSetpoint(FLOffset + 2.5);
  if(FROffset > 2.5) frontRight->SetSetpoint(FROffset - 2.5);
  else frontRight->SetSetpoint(FROffset + 2.5);
  if(RLOffset > 2.5) rearLeft->SetSetpoint(RLOffset - 2.5);
  else rearLeft->SetSetpoint(RLOffset + 2.5);
  if (RROffset > 2.5) rearRight->SetSetpoint(RROffset - 2.5);
  else rearRight->SetSetpoint(RROffset + 2.5);
   */

  // frontLeft->SetSetpoint(frontLeftPos->GetAverageVoltage());
  // frontRight->SetSetpoint(frontRightPos->GetAverageVoltage());
  // rearLeft->SetSetpoint(rearLeftPos->GetAverageVoltage());
  // rearRight->SetSetpoint(rearRightPos->GetAverageVoltage());

  frontLeft->Enable();
  frontRight->Enable();
  rearLeft->Enable();
  rearRight->Enable();
}
