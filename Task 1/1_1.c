#include "simpletools.h"
#include "abdrive.h"
#include "simulator.h"

int main(void){
    simulator_startNewSmokeTrail();
    drive_goto(102,-103);
    simulator_stopSmokeTrail();

    return 0;
}
