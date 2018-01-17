#include "simpletools.h"                        // Library includes
#include "abdrive.h"

int main()                                      // main function
{
  while(1)
    {
      drive_goto(50,50);
      pause(10);
      drive_goto(26, -25);
      pause(10);
    }
}
