#include "simpletools.h"
#include "abdrive.h"
#include <math.h>
#include <stdio.h>

//Lengths must be multiples of 10
#define xLength 30
#define yLength 50
#define gapLength 30
#define delay 1

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
  pause(delay);
  // / part of A
  simulator_startNewSmokeTrail();
  drive_goto(diagonal,diagonal);
  pause(delay);
  drive_goto(40,-40);
  pause(delay);
  // \ part of A
  drive_goto(diagonal+15,diagonal+15);
  pause(delay);
  drive_goto(-0.6*diagonal,-0.6*diagonal);
  pause(delay);
  drive_goto(-20,20);
  pause(delay);
  // - part of A
  drive_goto(-0.5*base,-0.5*base);
  pause(delay);
  //Move robot to next position
  drive_goto(0.5*base,0.5*base);
  pause(delay);
  drive_goto(20,-20);
  pause(delay);
  drive_goto(0.6*diagonal-15,0.6*diagonal-15);
  simulator_stopSmokeTrail();
  pause(delay);
  drive_goto(-20,20);
  pause(delay);
  drive_goto(gapLength,gapLength);
  //Letter Complete
  pause(delay);
}

void E(){
  drive_goto(-26,25);
  pause(delay);
  //Draw | part of E
  simulator_startNewSmokeTrail();
  drive_goto(yLength, yLength);
  pause(delay);
  drive_goto(26,-25);
  pause(delay);
  //Draw top and middle - for E
  for (int i = 0; i < 2; i++){
    simulator_startNewSmokeTrail();
    drive_goto(xLength, xLength);
    pause(delay);
    drive_goto(-xLength, -xLength);
    simulator_stopSmokeTrail();
    pause(delay);
    drive_goto(26,-25);
    drive_goto(yLength/2, yLength/2);
    pause(delay);
    drive_goto(-26, 25);
    pause(delay);
  }
  //Draw _ of E
  simulator_startNewSmokeTrail();
  drive_goto(xLength, xLength);
  simulator_stopSmokeTrail();
  drive_goto(gapLength,gapLength);
  //Letter Complete
  pause(delay);
}

void F(){
  drive_goto(-26,25);
  pause(delay);
  //Draw | part of F
  simulator_startNewSmokeTrail();
  drive_goto(yLength, yLength);
  pause(delay);
  drive_goto(26,-25);
  pause(delay);
  // Draw the - Parts of F
  for (int i = 0; i < 2; i++){
    simulator_startNewSmokeTrail();
    drive_goto(xLength, xLength);
    simulator_stopSmokeTrail();
    pause(delay);
    if (i == 0){
      simulator_startNewSmokeTrail();
      drive_goto(-xLength, -xLength);
      pause(delay);
      simulator_stopSmokeTrail();
      drive_goto(26,-25);
      drive_goto(yLength/2, yLength/2);
      pause(delay);
      drive_goto(-26, 25);
      pause(delay);
    }
  }
  //Letter Complete
  pause(1000);
  //Reposition for next letter
  drive_goto(26,-25);
  pause(delay);
  drive_goto(yLength/2, yLength/2);
  pause(delay);
  drive_goto(-26,25);
  pause(delay);
  drive_goto(gapLength,gapLength);
  pause(delay);
}

void H(){
  drive_goto(-26,25);
  pause(delay);
  //Draw left | of H
  simulator_startNewSmokeTrail();
  drive_goto(yLength+10,yLength+10);
  pause(delay);
  drive_goto(-yLength/2-0.1*yLength, -yLength/2-0.1*yLength);
  pause(delay);
  //Draw - part of H
  drive_goto(26,-25);
  pause(delay);
  drive_goto(xLength,xLength);
  pause(delay);
  drive_goto(-26,25);
  pause(delay);
  //Draw right | part of H
  drive_goto(yLength/2+0.1*yLength, yLength/2+0.1*yLength);
  pause(delay);
  drive_goto(-yLength-10,-yLength-10);
  pause(delay);
  simulator_stopSmokeTrail();
  //Move to next position
  drive_goto(26,-25);
  pause(delay);
  drive_goto(gapLength,gapLength);
  //Letter Complete
  pause(delay);
}

void I(){
  pause(delay);
  drive_goto(-26,25);  //turn anti-clockwise(90 degree)
  pause(delay);
  simulator_startNewSmokeTrail();
  drive_goto(yLength,yLength);  //up, letter finished  [wheels at the back]
  simulator_stopSmokeTrail();
  pause(delay);

  //change to the initial state and go to the next starting point
  drive_goto(-yLength,-yLength);  //backwards
  pause(delay);
  drive_goto(26,-25);  //turn anti-clockwise(90)
  pause(delay);
  drive_goto(gapLength,gapLength);
}

void K(){
  drive_goto(-26,25);   //turn clockwise(90 degree)
  pause(delay);
  simulator_startNewSmokeTrail();
  drive_goto(yLength,yLength);  //up   [wheels at the back]
  pause(delay);
  drive_goto(-yLength/2,-yLength/2); //backwards  [wheels at the front]
  pause(delay);
  drive_goto(13,-13);  //turn clockwise(45 degree)
  pause(delay);

  if(xLength>=yLength/2){
    drive_goto(yLength*sqrt(2)/2,yLength*sqrt(2)/2); //draw the /  [wheels at the back]
    pause(delay);
    drive_goto(-yLength*sqrt(2)/2,-yLength*sqrt(2)/2);  //backwards  [wheels at the front]
    pause(delay);
    drive_goto(26,-25); //turn clockwise(90 degree)
    pause(delay);
    drive_goto(yLength*sqrt(2)/2+15,yLength*sqrt(2)/2+ 15);  //draw the \, letter finished  [wheels at the back]
    pause(delay);
    drive_goto(-15,-15);
    pause(delay);
    //make the robot back to its initial state
    simulator_stopSmokeTrail();
    drive_goto(-13,13);  //turn anti-clockwise(45 degree)
    pause(delay);
    drive_goto(gapLength,gapLength);
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
    pause(delay);

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
  drive_goto(-26,25);  //clockwise(90)
    pause(delay);
    simulator_startNewSmokeTrail();
    drive_goto(yLength,yLength);  //up  [wheels at the back]
    pause(delay);
    drive_goto(-yLength,-yLength);  //backward
    pause(delay);
    drive_goto(26,-25);  //clockwise(90)
    pause(delay);
    drive_goto(xLength,xLength); //letter finished
    pause(delay);
    simulator_stopSmokeTrail();

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
