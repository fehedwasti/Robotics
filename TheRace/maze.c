#include <stdlib.h>
#include <time.h>

#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"

int baseSpeed = 41;
int maxForwardDist = 40;
int maxSideDist = 20;

typedef enum direction{
  up,   //0
  left, //1
  down, //2
  right //3
} direction;

direction facing = up;
int turns = 0;
int directions[300];
int direction_itr = 0;
int junctions[300];
int junc_itr = 0;
int flipCount = 0;
int final;
int x = 1;    //Robot co-ordinates
int y = 1;
int endPhase1 = 0;

int read_forward(){
  int dist = ping_cm(8);
  int clear = 1;
  if (dist < maxForwardDist){
    clear = 0;
  }
  return clear;
}

int read_left(){
  int left = 0;
  int clear = 1;
  for(int dacVal = 0; dacVal < 160; dacVal += 8){
    dac_ctr(26, 0, dacVal);
    freqout(11, 1, 38000);
    left += input(10);
  }
  if (left < maxSideDist){
    clear = 0;
  }
  return clear;
}

int read_right(){
  int right = 0;
  int clear = 1;
  for(int dacVal = 0; dacVal < 160; dacVal += 8){
    dac_ctr(27, 1, dacVal);
    freqout(1, 1, 38000);
    right += input(2);
  }
  if (right < maxSideDist){
    clear = 0;
  }
  return clear;
}

void printDirections(){
  //Print DIRECT directions
  printf("[");
  for (int i = 0; i <= direction_itr; i++){
    if (i != direction_itr){
      printf("%i, ", directions[i]);
    }
    else{
      printf("%i]\n", directions[i]);
    }
  }
}

void forward(int n){
  double tick_value = (10/3.25) * n;
  drive_goto(tick_value, tick_value);
}

void turnLeft(){
  drive_goto(-26,25);
  turns++;
  switch(facing){
    case up:
        facing = left;
        break;
    case left:
        facing = down;
        break;
    case down:
        facing = right;
        break;
    case right:
        facing = up;
        break;
  }
}

void turnRight(){
  drive_goto(26,-25);
  turns--;
  switch(facing){
    case up:
        facing = right;
        break;
    case left:
        facing = up;
        break;
    case down:
        facing = left;
        break;
    case right:
        facing = down;
        break;
  }
}

void backward(int n){
  double tick_value = -(10/3.25) * n;
  drive_goto(tick_value, tick_value);
}

void turn180(){
  if (flipCount % 2 == 0){
    drive_goto(51,-52);
  }
  else{
    drive_goto(-51,52);
  }
  flipCount++;

  switch (facing) {
    case up:
      facing = down;
      break;
    case left:
      facing = right;
      break;
    case down:
      facing = up;
      break;
    case right:
      facing = left;
      break;
  }
}

void storeDirection(direction thisWay){
  if (endPhase1 == 0){
    if ((x != 4) || (y != 4)){
      directions[direction_itr] = thisWay;
      direction_itr++;
    }
    else{
      directions[direction_itr] = thisWay;
      direction_itr++;
      printf("End of Phase 1\n");
      endPhase1 = 1;
      final = direction_itr;
    }
  }
}

void changeDirectionTo(direction thatWay){
  int change = thatWay - facing;
  if (change < 0){
    change += 4;
  }
  switch(change){
    case 1:
        turnLeft();
        break;
    case 2:
        turn180();
        break;
    case 3:
        turnRight();
        break;
  }
  facing = thatWay;
}

void fix_xy(){
  if (facing == 0){
    y++;
  }
  else if (facing == 1){
    x--;
  }
  else if (facing == 2){
    y--;
  }
  else if (facing == 3){
    x++;
  }
}

void checkAndGo(direction currentView){
  int check;

  switch(currentView){
    case up:
        changeDirectionTo(left);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x--;
          storeDirection(left);
          return;
        }

        changeDirectionTo(up);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y++;
          storeDirection(up);
          return;
        }

        changeDirectionTo(right);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x++;
          storeDirection(right);
          return;
        }

        changeDirectionTo(down);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y--;
          storeDirection(down);
          return;
        }
    case left:
        changeDirectionTo(down);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y--;
          storeDirection(down);
          return;
        }

        changeDirectionTo(left);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x--;
          storeDirection(left);
          return;
        }

        changeDirectionTo(up);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y++;
          storeDirection(up);
          return;
        }

        changeDirectionTo(right);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x++;
          storeDirection(right);
          return;
        }

    case down:

        changeDirectionTo(right);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x++;
          storeDirection(right);
          return;
        }

        changeDirectionTo(down);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y--;
          storeDirection(down);
          return;
        }

        changeDirectionTo(left);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x--;
          storeDirection(left);
          return;
        }

        changeDirectionTo(up);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y++;
          storeDirection(up);
          return;
        }

    case right:
        changeDirectionTo(up);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y++;
          storeDirection(up);
          return;
        }
        changeDirectionTo(right);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x++;
          storeDirection(right);
          return;
        }

        changeDirectionTo(down);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          y--;
          storeDirection(down);
          return;
        }

        changeDirectionTo(left);
        check = read_forward();
        if (check){
          forward(baseSpeed);
          x--;
          storeDirection(left);
          return;
        }

  }//end switch
}

void backup(int iterations){
  int reversing;
  int turnback = 0;
  for (int i = 0; i < iterations; i++){
    reversing = directions[direction_itr-1];
    if (turnback == 0){
      changeDirectionTo(reversing);
      backward(baseSpeed);
      if (reversing !=directions[direction_itr-2]){
        turnback = 1;
      }
    }
    else{
      changeDirectionTo((directions[direction_itr-1]+2) % 4);
      forward(baseSpeed);
    }
    if(reversing==up){
      y--;
    }
    else if(reversing == down){
      y++;
    }
    else if(reversing == left){
      x++;
    }
    else if(reversing == right){
      x--;
    }

    if (i == iterations-1){
      if (turnback == 0){
        if (read_right() == 1){
          turnRight();
          forward(baseSpeed);
          if (facing == 0){
            y++;
          }
          else if(facing == 1){
            x--;
          }
          else if (facing == 2){
            y--;
          }
          else if (facing == 3){
            x++;
          }
          if(endPhase1==0){
            storeDirection(facing);
          }
        }
      }
    }
    direction_itr--;
  }

}


void junction(){
  printDirections();
  int front = read_forward();
  int left = read_left();
  int right = read_right();
  if (left && right && front){
    junctions[junc_itr] = -100;
  }
  else if(left && right){
    junctions[junc_itr] = -100;
  }
  else if(left && front){
    junctions[junc_itr] = -100;
  }
  else if (front && right){
    junctions[junc_itr] = -100;
  }
  else if (front == 0 && left == 0 && right == 0){
    junctions[junc_itr] = 300; //deadend
    printf("DEADEND!!\n");
    int counter = 0;
    while(junctions[junc_itr] > 0){
      counter++;
      junc_itr--;
    }
    printf("counter: %i", counter);
    if (endPhase1 == 0){
      backup(counter);
    }
    else{
      turn180();
      pause(1);
      forward(baseSpeed);
      fix_xy();
    }

  }
  else{
    junctions[junc_itr] = 200;
  }
  printf("Junction?: %i\n", junctions[junc_itr]);
  junc_itr++;
}

void phase1(){
  forward(baseSpeed);
  directions[direction_itr] = 0;
  direction_itr++;
  junction();
  do{
    print("current loaction: (%d,%d)\n", x, y);
    print("currently facing: %d\n", facing);
    print("\n");
    checkAndGo(facing);
    junction();
  }
  while ((x != 1) || (y != 1));

  changeDirectionTo(up);
  backward(baseSpeed-10);
}

void phase2(){
  pause(1);
  printDirections();
  int n1, n2,n3;
  for (int i = 0; i < final;){
    n1 = i + 1;
    n2 = i + 2;
    n3 = i + 3;
    if (directions[i]==directions[n1]&& directions[n1] == directions[n2]){
      if (directions[n2] == directions[n3]){
        changeDirectionTo(directions[i]);
        forward(baseSpeed*4);
        i += 4;
      }
      else{
        changeDirectionTo(directions[i]);
        forward(baseSpeed*3);
        i += 3;
      }

    }
    else if (directions[i] == directions[n1]){
      changeDirectionTo(directions[i]);
      forward(baseSpeed*2);
      i += 2;
    }
    else{
      changeDirectionTo(directions[i]);
      forward(baseSpeed);
      i++;
    }
  }
}

int main(void){
  simulator_startNewSmokeTrail();
  phase1();
  simulator_stopSmokeTrail();
  phase2();
  return 0;
}
