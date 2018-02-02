#include <stdio.h>
#include "ping.h"
#include "simpletools.h"
#include "abdrive.h"
#include "functions.c"

int main(){
    turn(17,-1) ;        //17.6 ;drive_goto(5,-5);
    angles[inDex]=17;
    inDex++;
    drive_ramp(28,28);
    moveAlongwall();
    printf("final distance=%d\n",ping_cm(8));
}
