#include "run.c"

int main()
{
    printf("\n----------------------------------------------------\n");
    printf("Something need to know:\n");
    printf("*In phase 1,in some cases this solution would let the robot go back to the starting point.\n\n");
    printf("*That is normal.But the problem is it might take a bit long time to finish the phase 1,usually around 12 min(Very sorry about that).\n\n");
    printf("*Please wait patiently.\n\n");
    printf("*Once a stage is finished information will be printed out to let you know.\n");
    printf("\n----------------------------------------------------\n");

    drive_speed(128,128);
    simulator_startNewSmokeTrail();
    printf("\n--------------------Preparing-----------------------\n");
    drive_goto(0.25*W_tick,0.25*W_tick);  //to get to the center of the start point 
    printf("\n          Reached center of the start square.       \n");
    printf("\n------------------PHASE 1 START---------------------\n");
    phase1();
    printf("\n------------------PHASE 1 FINISH----------------------\n");
    pause(1000);
    phase2();
    printf("\n------------------PHASE 2 FINISH--------------------\n");
    simulator_stopSmokeTrail();
    return 0;
}