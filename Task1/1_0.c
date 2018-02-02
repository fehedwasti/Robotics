#include "simpletools.h"
#include "abdrive.h"
#include "simulator.h"

int main(void) {
  drive_goto(150,150);
  pause(10);
  drive_goto(26,-25);
  pause(10);
  drive_goto(150,150);
  pause(10);
  drive_goto(-26,25);

  simulator_startNewSmokeTrail();
  drive_goto(-308, -308);
  pause(10);
  drive_goto(26,-25);
  pause(10);
  drive_goto(-308,-308);
  pause(10);
  drive_goto(-26,25);
  pause(10);
  drive_goto(300,300);
  pause(10);
  drive_goto(26,-25);
  pause(10);
  drive_goto(308,308);

  simulator_stopSmokeTrail();

  return 0;
}
