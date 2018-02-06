#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"


clock_t t;

void backtrack(int order[], int itr){
  //Turn 180 degrees
  int i,j,temp,temp2;
  drive_goto(-15,-15);
  pause(1);
  drive_goto(52,-50);
  pause(2000);
  simulator_startNewSmokeTrail();
  i = 0;
  j = itr;
  while(i<j){
    temp = order[i];
    temp2 = order[j];
    order[i] = temp2;
    order[j] = temp;
    i++;
    j--;
  }
  for (int i = 0; i <= itr; i++){
    printf("\n%i", order[i]);
  }
  for (int i = 0; i <= itr; i++){
    if (order[i] == 1){
      drive_speed(15,20);
      pause(100);
    }
    else if (order[i]== -1){
      drive_speed(20,15);
      pause(100);
    }
    else{
      drive_speed(20,20);
      pause(100);
    }
  }
  simulator_stopSmokeTrail();
}



int main(int argc, const char* argv[]){
  clock_t start, finish;
  double t_time;

  t = clock();
  // Drive ahead nice and slow
  int function_order[300];
  int iterator = 0;

  start = clock();
  drive_speed(64, 64);

simulator_startNewSmokeTrail();
  while(ping_cm(8) > 8)
    {
      long int lastCNT = CNT;


      // Read the left and right sensors
      int irLeft = 0;
      for(int dacVal = 0; dacVal < 160; dacVal += 8)  // <- add
        {                                               // <- add
          dac_ctr(26, 0, dacVal);                       // <- add
          freqout(11, 1, 38000);                        // <- add
          irLeft += input(10);
        }

      print("%f\n", (1.0 * (CNT - lastCNT)) / ms);


      int irRight = 0;
      for(int dacVal = 0; dacVal < 160; dacVal += 16)  // <- add
        {                                               // <- add
          dac_ctr(27, 1, dacVal);                       // <- add
          freqout(1, 1, 38000);                        // <- add
          irRight += input(2);
        }



      if (irLeft < irRight)
        {
          drive_speed(20, 15);
          function_order[iterator] = 1;
          iterator++;
        }
      else if (irLeft > irRight)
        {
          drive_speed(15,20);
          function_order[iterator] = -1;
          iterator++;
        }
      else
        {
          drive_speed(20, 20);
          function_order[iterator] = 25;
          iterator++;
        }


      printf("%d %d\n", irLeft, irRight);
      pause(100);
    }

  // Stop
  drive_speed(0, 0);
  for (int i = 0; i <= iterator; i++){
    printf("%i", function_order[i]);
  }
  simulator_stopSmokeTrail();
  backtrack(function_order, iterator);
  finish = clock();

  t = clock() - t;
  t_time = ((double)(finish - start))/CLOCKS_PER_SEC;
  printf("\n time taken: %f", t_time);
  return 0;
}
