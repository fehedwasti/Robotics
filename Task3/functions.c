#include "simpletools.h"
#include "abdrive.h"
#include "simulator.h"


int counter=0;
int angles[50];
int inDex=0;
//All turns are anticlockwise by default
//so you can pass direction as any value
//If you need clockwise, use -1 as a parameter.

void turn(int angle, int direction){
  int ticks = ceil(0.28407778 * angle);
  int ticks1 = floor(0.28407778 * angle);
  if (direction == -1)
    drive_goto(ticks, -ticks1);
  else
    drive_goto(-ticks, ticks1);
}

void detectWall(){
    int dist=ping_cm(8);
    printf("distance=%d\n",dist);

    if(dist<26){
        if(counter==0){
            turn(52,-1);  //52.8; drive_goto(15,-15)
            angles[inDex]=52;
            inDex++;
            counter++;
        }
        else if(counter==1){
            drive_goto((int)(dist-5)*10/3.25,(int)(dist-5)*10/3.25);

            counter++;
            int sum=0;
            for(int i=0;i<inDex;i++){
                sum+=angles[i];
            }
            printf("final direction:%d\n",sum);
            printf("adjusting...");
            turn(sum,1);
            return;
        }
    }
    else
      return;
}

void moveAlongwall(){
    int irLeft,irRight;
    low(26);                                      // D/A0 & D/A1 to 0 V
    low(27);

    while(counter<2){
        freqout(11, 1, 38000);
        irLeft = input(10);

        freqout(1, 1, 38000);
        irRight = input(2);

        printf("%cirRight=%d\tirLeft=%d\n",HOME,irRight,irLeft);

        if(((irRight==0)&&(irLeft==0))||((irRight==1)&&(irLeft==1))){
            turn(31,1);  //31.6; drive_goto(-9,9)
            angles[inDex]=-31;
            inDex++;
        }
        else{
            drive_goto(20,20);
        }

        detectWall();

        pause(10);
    }
}
