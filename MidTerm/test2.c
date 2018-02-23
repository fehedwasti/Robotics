#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"

int a,b,c,d; // a > b


void rightTurn(){
  drive_speed(a,b);
}
void leftTurn(){
  drive_speed(b,a);
}


void backtrack(int order[], int itr){

  //Turn 180 degrees
  drive_goto(-10,-10);
  pause(1);
  drive_goto(52,-50);
  pause(1);
  printf("\nPress enter to continue");
  char enter = 0;
  while (enter != '\r' && enter != '\n') { enter = getchar(); }
  int i,j,temp,temp2;

  simulator_startNewSmokeTrail();
  for (int i = itr; i > -1; i--){
    b = d;

    if (order[i] == 2){
      b = c;
      leftTurn();
    }
    else if (order[i] == -2){
      b = c;
      rightTurn();
    }
    else if (order[i] == 1){
      leftTurn();
    }
    else if (order[i]== -1){
      rightTurn();
    }
    else{
      drive_speed(20,20);
    }
    pause(145);
  }
  drive_speed(0,0);
  simulator_stopSmokeTrail();
}


int main(int argc, const char* argv[]){
  //set variables for calculating moved distance
  int lt=0,rt=0;
  int *left=&lt;
  int *right=&rt;
  int pre_lt=0,pre_rt=0;
  float dl=0,dr=0;
  float distance=0;   //distance moved by the robot relative to start
  float angle=0;
  float records[2]={0,0};

  printf("distance = %f, angle = %f", records[0], records[1]);

  clock_t start, finish;
  double t_time;

  int function_order[300];
  int iterator = 0;

  drive_speed(64, 64);

  simulator_startNewSmokeTrail();

  a = 27; b = a * 0.75; c = 0.6 * b; d = b;
  while(ping_cm(8) > 10) {
      b = d;
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
          b = c;
          rightTurn();
          function_order[iterator] = 2;
          iterator++;
      }

      else if (irRight < 3){
          b = c;
          leftTurn();
          function_order[iterator] = -2;
          iterator++;
      }

      else if (irLeft < irRight)
        {
          rightTurn();
          function_order[iterator] = 1;
          iterator++;
        }
      else if (irLeft > irRight)
        {
          leftTurn();
          function_order[iterator] = -1;
          iterator++;
        }
      else
        {
          drive_speed(a, a);
          function_order[iterator] = 5;
          iterator++;
        }


      printf("leftSensor = %d rightSensor = %d\n", irLeft, irRight);
      pause(100);


      drive_getTicks(left,right);
      dl=(*left-pre_lt)*3.25/10;  //cm
      dr=(*right-pre_rt)*3.25/10;  //cm

      angle=(dl-dr)/10.58;  //radius
      if(dl==dr)
        distance=dl;
      else
        distance=fabsf(angle*(dl+dr)/2);
      records[0]+=distance;
      records[1]+=angle;

      pre_lt=*left;
      pre_rt=*right;
    }

  // Stop
  drive_speed(0, 0);
  int wallDistance = ping_cm(8);
  printf("\nThe robot has moved %f cm and turned %f radians.\n",records[0],records[1]);
  printf("Distance to Wall: %i", wallDistance);
  simulator_stopSmokeTrail();

  backtrack(function_order, iterator);

  int dist = ping_cm(8);
  printf("final distance = %i\n", dist );

  return 0;
}
