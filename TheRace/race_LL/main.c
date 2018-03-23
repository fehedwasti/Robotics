#include "run.c"

int main()
{
    drive_speed(128,128);
    simulator_startNewSmokeTrail();
    printf("\n--------------------Preparing-----------------------\n");
    drive_goto(0.25*W_tick,0.25*W_tick);  //to get to the center of the start point 
    printf("\n          Reached center of the start square.       \n");
    printf("\n------------------PHASE 1 START---------------------\n");
    phase1();
    printf("\n------------------PHASE 1 FINISH----------------------\n");
    pause(2000);
    phase2();
    printf("\n------------------PHASE 2 FINISH--------------------\n");
    simulator_stopSmokeTrail();
    return 0;
}