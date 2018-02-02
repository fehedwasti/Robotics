#include "simpletools.h"
#include "abdrive.h"
#include "simulator.h"

//All turns are anticlockwise by default
//so you can pass direction as any value
//If you need clockwise, use -1 as a parameter.

void turn(int angle, int direction){
  int ticks = ceil(0.28407778 * angle);
  int ticks1 = floor(0.28407778 * angle);
  if (direction == -1)
    drive_goto(ticks, -ticks1);
  else
    drive_goto(-ticks, ticks1);
}
