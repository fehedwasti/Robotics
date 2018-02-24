#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
  //need to print out relative distance and angle.
  printf("\nThe robot has moved %f cm in a direction of %f degree.\n",records[0],records[1]);
  
  //Go Back to start
  backtrack();

  int dist = ping_cm(8);
  printf("final distance = %i\n", dist );

  return 0;
}
