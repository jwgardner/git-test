#include "ShootCyclePart1.h"
#include "DefeedShoot.h"
#include "PositionDrive.h"
#include "ScriptCamDrive.h"
#include "SetWinchPosition.h"

ShootCyclePart1::ShootCyclePart1(int side) {

  AddParallel(new SetWinchPosition(3, true, 1));
  AddParallel(new DefeedShoot(2));
  AddSequential(new PositionDrive(
      0, side)); // ScriptCamDrive("DriveCam", 0, 0, 0.35, 0));

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
