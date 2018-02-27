#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"

#include "functions.c"

int main(int argc, const char* argv[]){
  //Move Forward and save path.
  forward();
  // Stop
  drive_speed(0, 0);
  //Measure Wall distance
  int wallDistance = ping_cm(8);
  printf("\nThe robot has moved %f cm and turned %f radians.\n",records[0],records[1]);
  printf("Distance to Wall: %i", wallDistance);
  //Go Back to start
  backtrack();

  int dist = ping_cm(8);
  printf("final distance = %i\n", dist );

  return 0;
}
