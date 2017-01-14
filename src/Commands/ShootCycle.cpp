#include "ShootCycle.h"
#include "../Robot.h"
#include "DeFeed.h"
#include "DefeedShoot.h"
#include "DisableWinchControl.h"
#include "Feed.h"
#include "PositionDrive.h"
#include "ScriptCamDrive.h"
#include "SetWheelsTwist.h"
#include "SetWinchPosition.h"
#include "Shoot.h"
#include "ShootCyclePart1.h"
#include "StopShoot.h"

ShootCycle::ShootCycle(int side) {

  AddSequential(new ShootCyclePart1(side));

  AddParallel(new Feed(2));
  AddSequential(
      new SetWheelsTwist(2)); // ScriptCamDrive("DriveCam", 0, 0, 0.35, 1));

  AddParallel(new SetWinchPosition(2, false, 0));
  AddSequential(new StopShoot());

  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
}
