#include "simpletools.h"                        // Library includes
#include "abdrive.h"

int main(){
    simulator_startNewSmokeTrail();
    drive_goto(102,-103);
    simulator_stopSmokeTrail();
}
