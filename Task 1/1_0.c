#include "simpletools.h"                        // Library includes
#include "abdrive.h"

int main()                                      // main function
{
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
}
