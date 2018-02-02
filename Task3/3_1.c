#include <stdio.h>
#include "ping.h"
#include "simpletools.h"
#include "abdrive.h"
#include "functions.c"

int main(){
    drive_goto(5,-5);
    angles[inDex]=5;
    inDex++;
    //int dist=ping_cm(8);
    //printf("distance=%d\n",dist);
    drive_ramp(28,28);
    moveAlongwall();
    printf("final distance=%d\n",ping_cm(8));
}
