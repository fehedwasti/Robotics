#include <stdio.h>
#include "simpletools.h"
#include "abdrive.h"
#include "simulator.h"
#include "functions.c"
#include "ping.h"

int main(void){
  turn(90,1);
  int distance = ping_cm(8);
  printf("%i", distance);
  if (distance < 10){
    drive_goto(-20,-20);
  }
}
