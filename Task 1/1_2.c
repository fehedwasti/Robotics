#include "simpletools.h"
#include "abdrive.h"
#include <math.h>
#include <stdio.h>

//Lengths must be multiples of 10
#define xLength 60
#define yLength 100
#define gapLength 30
#define delay 1
#define delay2 1  

double sine(double value){
  value = value * M_PI/180;
  return sin(value);
}

double cosine(double value){
  value = value * M_PI/180;
  return cos(value);
}

void A(){
  double b = (yLength/ sine(70));
  int diagonal = floor(b);
  int base = floor(2*diagonal*cosine(70));

  drive_goto(-20,20);
  pause(1);
  // / part of A
  simulator_startNewSmokeTrail();
  drive_goto(diagonal,diagonal);
  pause(1);
  drive_goto(40,-40);
  pause(1);
  // \ part of A
  drive_goto(diagonal+15,diagonal+15);
  pause(1);
  drive_goto(-0.6*diagonal,-0.6*diagonal);
  pause(1);
  drive_goto(-20,20);
  pause(1);
  // - part of A
  drive_goto(-0.5*base,-0.5*base);
  pause(1);
  drive_goto(0.5*base,0.5*base);
  pause(1);
  drive_goto(20,-20);
  pause(1);
  drive_goto(0.6*diagonal-15,0.6*diagonal-15);
  simulator_stopSmokeTrail();
  pause(1);
  drive_goto(-20,20);
  pause(1);
  drive_goto(30,30);
  //Letter Complete
  pause(10);
}

void E(){
  drive_goto(-26,25);
  pause(1);
  simulator_startNewSmokeTrail();
  drive_goto(yLength, yLength);
  pause(1);
  drive_goto(26,-25);
  pause(1);
  for (int i = 0; i < 2; i++){
    simulator_startNewSmokeTrail();
    drive_goto(xLength, xLength);
    pause(1);
    drive_goto(-xLength, -xLength);
    simulator_stopSmokeTrail();
    pause(1);
    drive_goto(26,-25);
    drive_goto(yLength/2, yLength/2);
    pause(1);
    drive_goto(-26, 25);
    pause(1);
  }
  simulator_startNewSmokeTrail();
  drive_goto(xLength, xLength);
  simulator_stopSmokeTrail();
  drive_goto(30,30);
  //Letter Complete
  pause(10);
}

void F(){
  drive_goto(-26,25);
  pause(1);
  simulator_startNewSmokeTrail();
  drive_goto(yLength, yLength);
  pause(1);
  drive_goto(26,-25);
  pause(1);
  for (int i = 0; i < 2; i++){
    simulator_startNewSmokeTrail();
    drive_goto(xLength, xLength);
    simulator_stopSmokeTrail();
    pause(1);
    if (i == 0){
      simulator_startNewSmokeTrail();
      drive_goto(-xLength, -xLength);
      pause(1);
      simulator_stopSmokeTrail();
      drive_goto(26,-25);
      drive_goto(yLength/2, yLength/2);
      pause(1);
      drive_goto(-26, 25);
      pause(1);
    }
  }
  //Letter Complete
  pause(1000);
  //Reposition for next letter
  drive_goto(26,-25);
  pause(1);
  drive_goto(yLength/2, yLength/2);
  pause(1);
  drive_goto(-26,25);
  pause(1);
  drive_goto(30,30);
  pause(1);
}

void H(){
  drive_goto(-26,25);
  pause(1);
  simulator_startNewSmokeTrail();
  drive_goto(yLength+10,yLength+10);
  pause(1);
  drive_goto(-yLength/2-0.1*yLength, -yLength/2-0.1*yLength);
  pause(1);
  drive_goto(26,-25);
  pause(1);
  drive_goto(xLength,xLength);
  pause(1);
  drive_goto(-26,25);
  pause(1);
  drive_goto(yLength/2+0.1*yLength, yLength/2+0.1*yLength);
  pause(1);
  drive_goto(-yLength-10,-yLength-10);
  pause(1);
  simulator_stopSmokeTrail();
  drive_goto(26,-25);
  pause(1);
  drive_goto(30,30);
  //Letter Complete
  pause(10);
}

void I(){
  drive_goto(xLength/4,xLength/4);  //go to the middle position  [wheels at the front]
  pause(delay2);
  drive_goto(-26,25);  //turn anti-clockwise(90 degree)
  pause(delay);
  simulator_startNewSmokeTrail();
  drive_goto(yLength,yLength);  //up, letter finished  [wheels at the back]  
  pause(delay2);
  simulator_stopSmokeTrail();

  //change to the initial state and go to the next starting point
  drive_goto(-yLength,-yLength);  //backwards
  pause(delay);
  drive_goto(26,-25);  //turn anti-clockwise(90)
  pause(delay);
  drive_goto(xLength/2+gapLength,xLength/2+gapLength);
}

void K(){
  drive_goto(26,-25);   //turn clockwise(90 degree)
  pause(delay2);
  simulator_startNewSmokeTrail();
  drive_goto(-yLength,-yLength);  //up   [wheels at the back]
  pause(delay);
  drive_goto(yLength/2,yLength/2); //backwards  [wheels at the front]
  pause(delay);
  drive_goto(13,-13);  //turn clockwise(45 degree)
  pause(delay);

  if(xLength>=yLength/2){
    drive_goto(-yLength*sqrt(2)/2,-yLength*sqrt(2)/2); //draw the /  [wheels at the back]
    pause(delay);
    drive_goto(yLength*sqrt(2)/2,yLength*sqrt(2)/2);  //backwards  [wheels at the front]
    pause(delay);
    drive_goto(-26,25); //turn anti-clockwise(90 degree)
    pause(delay);
    drive_goto(yLength*sqrt(2)/2,yLength*sqrt(2)/2);  //draw the \, letter finished  [wheels at the back]
    simulator_stopSmokeTrail();
    pause(delay2);

    //go to the next starting point
    drive_goto(-13,13);  //turn anti-clockwise(45 degree)
    pause(delay);
    drive_goto((xLength-yLength/2)+gapLength,(xLength-yLength/2)+gapLength);
    pause(delay);
  }
  else{
    drive_goto(-sqrt(2)*xLength,-xLength*sqrt(2)); //draw the /  [wheels at the back]
    pause(delay);
    drive_goto(xLength*sqrt(2),xLength*sqrt(2));  //backwards  [wheels at the front]
    pause(delay);
    drive_goto(26,-25); //turn clockwise(90 degree)
    pause(delay);
    drive_goto(-xLength*sqrt(2),-xLength*sqrt(2));  //draw the \  [wheels at the back]
    simulator_stopSmokeTrail();
    pause(delay2);

    //go to the next starting point
    drive_goto(13,-13);  //turn clockwise(45 degree)
    pause(delay);
    drive_goto(-(yLength/2-xLength),-(yLength/2-xLength));  //go to the bottom of the letter  [wheels at the back]
    pause(delay);
    drive_goto(26,-25); //turn clockwise(90 degree)
    pause(delay);
    drive_goto(gapLength,gapLength);
    pause(delay);
  }
  
}

void L(){
  drive_goto(26,-25);  //clockwise(90)
    pause(delay);    
    drive_goto(-yLength,-yLength);  //up  [wheels at the back]
    pause(delay2);
    simulator_startNewSmokeTrail();
    drive_goto(yLength,yLength);  //backward
    pause(delay);
    drive_goto(-26,25);  //clockwise(90)
    pause(delay);
    drive_goto(xLength,xLength); //letter finished
    simulator_stopSmokeTrail();
    pause(delay2);
    
    drive_goto(gapLength,gapLength); //go to the next starting point
}

int main(void){
  //Move robot to left side of canvas
  drive_goto(-200,-200);

  char input[100];
  printf("Enter text: \n");
  scanf("%s", input);

  for (int i = 0; i < strlen(input); i++){
    char letter = input[i];
    printf("%c\n", letter);

    switch(letter){
      case 'A': A(); break;
      case 'E': E(); break;
      case 'F': F(); break;
      case 'H': H(); break;
      case 'I': I(); break;
      case 'K': K(); break;
      case 'L': L(); break;
      default:
          printf("Enter letters in CAPS \n");
    }

  }
  //A();
  return 0;
}
