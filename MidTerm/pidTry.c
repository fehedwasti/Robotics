#include <stdio.h>
#include "abdrive.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"
#include <math.h>

float records[2]={0,0};
int histories[500];
int Index=0;

void back()
{
    drive_goto(52,-52);
    for(int i=Index-1;i>=0;i-=2)
    {
        drive_speed(histories[i],histories[i-1]);
        //same with the behaviour in the loop in run()
        pause(500);
        drive_speed(0,0);
    }
}

void run()
{
    //default speed
    int Vl=64,Vr=64;
    //output speed
    int vLeft,vRight;

    //set ping sensor
    int dist=ping_cm(8);
    printf("dist=%d\n",dist);

    //set ir sensor
    int irLeft,irRight;
    low(26);                                      // D/A0 & D/A1 to 0 V
    low(27);

    //set PID controller parameter
    int previous_errorL=0,previous_errorR=0;
    int integralL=0,integralR=0;
    int errorL,derivativeL;
    int errorR,derivativeR;
    float outputL,outputR;
    int T=500;   //sampling time
    int Ti=500;  //integral time
    int Td=500;  //derivative time
    float Kp=0.2*5/3;//Kp=1.4; the calibration of P (1/Kp) is 0.6
    float Ki=Kp*T/Ti;
    float Kd=Kp*Td/T;

    //set variables for calculating moved distance
    int lt=0,rt=0;
    int *left=&lt;
    int *right=&rt;
    int pre_lt,pre_rt;
    float dl=0,dr=0;    //distance moved by two wheels
    float distance=0;   //distance moved by the robot
    float angle=0;

    while(dist>20)
    {
        printf("dist = %d\n",dist);

        //get process variables
        freqout(11, 1, 38000);
        irLeft = input(10);
        freqout(1, 1, 38000);
        irRight = input(2);

        //PID controller
        errorL=irLeft-0;
        errorR=irRight-0;
        printf("errorL=%d,errorR=%d\n",errorL,errorR);

        integralL=integralL+errorL*Ti;
        integralR=integralR+errorR*Ti;
        printf("integralL=%d,integralR=%d\n",integralL,integralR);

        derivativeL=(errorL-previous_errorL)/Td;
        derivativeR=(errorR-previous_errorR)/Td;
        //derivativeL=derivativeR=0;
        printf("derivativeL=%d,derivativeR=%d\n",derivativeL,derivativeR);


        outputL=Kp*errorL+Ki*integralL+Kd*derivativeL;
        outputR=Kp*errorR+Ki*integralR+Kd*derivativeR;
        printf("outputL=%f,outputR=%f\n",outputL,outputR);

        vLeft=Vl-(int)outputL%Vl;
        vRight=Vr-(int)outputR%Vr;
        drive_speed(vLeft,vRight);
        histories[Index]=vLeft;
        histories[Index+1]=vRight;
        Index+=2;
        printf("Vl=%d,Vr=%d\n",Vl-(int)outputL%Vl,Vr-(int)outputR%Vr);

        //calculate moved distance
        drive_getTicks(left,right);
        dl=(*left-pre_lt)*3.25/10;  //cm
        dr=(*right-pre_rt)*3.25/10;  //cm
        printf("dl=%f,dr=%f\n",dl,dr);
        angle=(dl-dr)/10.58;  //radius
        if(dl==dr)
          distance=dl;
        else
          distance=abs(angle*(dl+dr)/2);
        records[0]+=distance;
        records[1]+=angle;

        pre_lt=*left;
        pre_rt=*right;
        previous_errorL=errorL;
        previous_errorR=errorR;
        dist=ping_cm(8);
        pause(T);
        drive_speed(0,0);
    }
    drive_speed(0,0);
}

int main()
{
    simulator_startNewSmokeTrail();
    run();
    printf("\nThe robot has moved %f cm and turned %f degree.\n",records[0],records[1]);
    pause(1000);
    back();
    simulator_stopSmokeTrail();
}
