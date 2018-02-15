#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"

int a,b; // a > b


void right(){
  drive_speed(a,b);
}
void left(){
  drive_speed(b,a);
}


void backtrack(int order[], int itr){

  printf("\nPress enter to continue");
  char enter = 0;
  while (enter != '\r' && enter != '\n') { enter = getchar(); }
  int i,j,temp,temp2;

  //Turn 180 degrees
  //drive_goto(-15,-15);
  pause(1);
  drive_goto(52,-50);
  pause(1);

  simulator_startNewSmokeTrail();
  for (int i = itr; i > -1; i--){
    b = 15;

    if (order[i] == 2){
      b = 12;
      left();
    }
    else if (order[i] == -2){
      b = 12;
      right();
    }
    else if (order[i] == 1){
      left();
    }
    else if (order[i]== -1){
      right();
    }
    else{
      drive_speed(20,20);
    }
    pause(150);
  }
  simulator_stopSmokeTrail();
}


int main(int argc, const char* argv[]){
  clock_t start, finish;
  double t_time;

  // Drive ahead nice and slow
  int function_order[300];
  int iterator = 0;

  drive_speed(64, 64);

  simulator_startNewSmokeTrail();
  while(ping_cm(8) > 10) {
      a = 20; b = 15;
      long int lastCNT = CNT;


      // Read the left and right sensors
      int irLeft = 0;
      for(int dacVal = 0; dacVal < 160; dacVal += 8){
          dac_ctr(26, 0, dacVal);
          freqout(11, 1, 38000);
          irLeft += input(10);
        }

      int irRight = 0;
      for(int dacVal = 0; dacVal < 160; dacVal += 16){
          dac_ctr(27, 1, dacVal);
          freqout(1, 1, 38000);
          irRight += input(2);
        }

      if (irLeft < 3){
          b = 12;
          right();
          function_order[iterator] = 2;
          iterator++;
      }

      else if (irRight < 3){
          b = 12;
          left();
          function_order[iterator] = -2;
          iterator++;
      }

      else if (irLeft < irRight)
        {
          right();
          function_order[iterator] = 1;
          iterator++;
        }
      else if (irLeft > irRight)
        {
          left();
          function_order[iterator] = -1;
          iterator++;
        }
      else
        {
          drive_speed(20, 20);
          function_order[iterator] = 5;
          iterator++;
        }


      printf("%d %d\n", irLeft, irRight);
      pause(100);

    }

  // Stop
  drive_speed(0, 0);
  int wallDistance = ping_cm(8);
  printf("Distance to Wall: %i", wallDistance);
  simulator_stopSmokeTrail();
  backtrack(function_order, iterator);

  return 0;
}
