#include <stdio.h>
#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"
#include <math.h>

int a,b,c,d;
int order[300];
int itr = 0;

//set variables for calculating moved distance
int lt=0,rt=0;
int *left=&lt;
int *right=&rt;
int pre_lt=0,pre_rt=0;
float tickL=0,tickR=0;
float distance=0;   //distance moved by the robot relative to start
float angle=0;
float pre_angle=0;
float dx=0,dy=0;
float sumx=0,sumy=0;
float rl=0,rr=0,rm=0;
float p=0,q=0;
float records[2]={0,0};

void rightTurn(){
  drive_speed(a,b);
}
void leftTurn(){
  drive_speed(b,a);
}

void forward(){
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
          order[itr] = 2;
          itr++;
      }

      else if (irRight < 3){
          b = c;
          leftTurn();
          order[itr] = -2;
          itr++;
      }

      else if (irLeft < irRight)
        {
          rightTurn();
          order[itr] = 1;
          itr++;
        }
      else if (irLeft > irRight)
        {
          leftTurn();
          order[itr] = -1;
          itr++;
        }
      else
        {
          drive_speed(a, a);
          order[itr] = 5;
          itr++;
        }

      printf("leftSensor = %d rightSensor = %d\n", irLeft, irRight);
      pause(100);

      drive_getTicks(left,right);
      tickL=*left-pre_lt; 
      tickR=*right-pre_rt;

      angle=(tickL-tickR)/(105.8/3.25);  //radius

      if(angle==0)
      {
        sumx+=0;
        sumy+=tickL;
      }
      else
      {
        rl=tickL/angle;   //ticks
        rr=tickR/angle;
        rm=(rl+rr)/2;

        p=cos(pre_angle)*rm;//x of the last point from the center of the circle
        q=cos(pre_angle+angle)*rm;//x of the current point from...
        dx=p-q;
        p=sin(pre_angle)*rm;
        q=sin(pre_angle+angle)*rm;
        dy=q-p;

        sumx+=dx;
        sumy+=dy;
      }
      pre_angle+=angle;
      pre_lt=*left;
      pre_rt=*right;
    }
    simulator_stopSmokeTrail();
    records[0]=sqrt(sumx*sumx+sumy*sumy)*0.325;
    records[1]=atan(sumx/sumy)*180/3.1415;//relative angle

    int wallDistance=ping_cm(8);
    printf("Distance to Wall: %i", wallDistance);
    //Turn 180 degrees
    drive_goto(-10,-10);
    pause(1);
    drive_goto(52,-50);
    pause(1);
}

void backtrack(){
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
