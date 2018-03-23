#include "run.c"

int main()
{
    printf("\n----------------------------------------------------\n");
    printf("Something need to know:\n");
    printf("*This solution would let the robot go back to the starting \n point whenever it meets the finishing point or a visited junction.\n");
    printf(" So sorry it might take a bit long time to finish the phase 1.\n\n");
    printf("*Once a step is finished information will be printed out to let you know.\n");
    printf("\n----------------------------------------------------\n");

    //drive_setRampStep(64);
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
