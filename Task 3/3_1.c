#include <stdio.h>
#include "ping.h"
#include "simpletools.h"
#include "abdrive.h"

int counter=0;
int angles[50];
int inDex=0;

void detectWall()
{
    int dist=ping_cm(8);
    printf("distance=%d\n",dist);

    if(dist<20)
    {
        if(counter==0)
        {
            drive_goto(15,-15);
            angles[inDex]=15;
            inDex++;
            counter++;
        }
        else if(counter==1)
        {
            drive_goto((int)(dist-5)*10/3.25,(int)(dist-5)*10/3.25);
            counter++;
            for(int i=0;i<inDex;i++)
            {
                drive_goto(-angles[i],angles[i]);
            }
            return;
        }
    }
    else
    return;
}

void moveAlongwall()
{
    int irLeft,irRight;
    low(26);                                      // D/A0 & D/A1 to 0 V
    low(27);

    while(counter<2)                                      
    {
        freqout(11, 1, 38000);                      
        irLeft = input(10);                         

        freqout(1, 1, 38000);                       
        irRight = input(2);

        printf("%cirRight=%d\tirLeft=%d\n",HOME,irRight,irLeft);
        
        if(((irRight==0)&&(irLeft==0))||((irRight==1)&&(irLeft==1)))
        {
            drive_goto(-8,8);
            angles[inDex]=-8;
            inDex++;
        }
        else
        {
            //drive_goto(-irLeft*10+irRight*10,-irRight*10+irLeft*10);
            drive_goto(23,23);
        }
        
        detectWall();

        pause(10);                                 
    }
}

int main()                                      // main function
{
    drive_goto(5,-5);
    angles[inDex]=5;
    inDex++;
    //int dist=ping_cm(8);
    //printf("distance=%d\n",dist);
    drive_ramp(28,28);
    moveAlongwall();
}
