#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"

int directions[300];
int itr = 0;


void forward(int n){
  double tick_value = (10/3.25) * n;
  drive_goto(tick_value, tick_value);
}

void backup(int n){
  double tick_value = -(10/3.25) * n;
  drive_goto(tick_value, tick_value);
}

int readLeft(){
  int irLeft = 0;
  for(int dacVal = 0; dacVal < 160; dacVal += 8){
      dac_ctr(26, 0, dacVal);
      freqout(11, 1, 38000);
      irLeft += input(10);
    }
    return irLeft;
}
int readRight(){
  int irRight = 0;
  for(int dacVal = 0; dacVal < 160; dacVal += 16){
      dac_ctr(27, 1, dacVal);
      freqout(1, 1, 38000);
      irRight += input(2);
    }
  return irRight;
}
void phase1(){
  int dist,forwarditr;

  for(int i = 0; i < 5; i++){
    int forwarditr = 0;
    dist = ping_cm(8);
    while (dist > 20){
      forward(20);
      forwarditr++;
      printf("%i \n", dist);
      dist = ping_cm(8);
    }
    if (dist < 20){
      directions[itr] = forwarditr * 20;
      itr++;
      if (directions[itr-2] == -90){
        directions[itr] = -100;
        itr++;
        drive_goto(-26,25);
      }
      else{
        directions[itr] = -90;
        itr++;
        drive_goto(26,-25);
        int left = readLeft();
        int right = readRight();
        printf("%i, %i \n", left, right);
      }

    }

  }

  //Print FAST ROUTE
  printf("[");
  for (int i = 0; i <= itr; i++){
    if (i != itr){
      printf("%i, ", directions[i]);
    }
    else{
      printf("%i]\n", directions[i]);
    }
  }
}

void midPhase(){
  for (int i = itr-1; i >= 0; i--){
    if (directions[i] >= 0){
      backup(directions[i]);
    }
    else if (directions[i] == -90){
      drive_goto(-26, 25);
    }
    else{
      drive_goto(26, -25);
    }
  }
}

void phase2(){
  for (int i = 0; i <= itr; i++){
    if (directions[i] >= 0){
      forward(directions[i]);
    }
    else if (directions[i] == -90){
      drive_goto(26, -25);
    }
    else{
      drive_goto(-26, 25);
    }
  }
}


int main(void){
  printf("\n HELLO \n");
  simulator_startNewSmokeTrail();
  phase1();
  simulator_stopSmokeTrail();
  midPhase();
  phase2();
  return 0;
}
