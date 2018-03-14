int turns = 0;    //global?
//To implement in your Turn Functions...
//each time the robot turns left, turns ++      Doesn't apply
//each time the robot turns right, turns --     Doesn't apply
// if turns < 0, turns += 4;
// else turns %= 4;

//ie  turns = 0 --> Currently Facing up
//    turns = 1 --> Currently Facing left
//    turns = 2 --> Currently Facing down
//    turns = 3 --> Currently Facing right


//In storeRoute Function
//after storing route (0,1,2 or 3)
int previousRoute = route[direction_counter - 1];
int currentRoute = route[direction_counter];

if (previousRoute < currentRoute){
  while (previousRoute != currentRoute){
    turns++;
    previousRoute++;
  }
}
else{
  while (previousRoute != currentRoute){
    turns--;
    previousRoute--;
  }
}

if (turns < 0){
  turns += 4;
}
else{
  turns %= 4;
}

void turnLeft(){
  drive_goto(-26, 25);
}
void turnRight(){
  drive_goto(26,-25);
}


//call backup(counter) after my while loop.
void backup(int iterations){
  if (turns < 0){
    turns += 4;
  }
  else{
    turns %= 4;
  }
  for (int i = 0; i <= iterations; i++){
    if (route[direction_counter] == 0){   //robot moved up...
      if (turns > 2){ //ie 3
        turnRight();
        turns--;
      }
      else{
        while(turns != 2){
          turnLeft();
          turns++;
        }
      }
      //Robot should now be facing down (turns = 2).
      y--;
    }
    else if (route[direction_counter] == 1){   //robot moved left...
      if (turns < 1){ //ie 0
        turnRight();
        turns--;
      }
      else{
        while(turns != 3){
          turnLeft();
          turns++;
        }
      }
      //Robot should now be facing right (turns = 3).
      x++;
    }

    else if (route[direction_counter] == 2){   //robot moved down ...
      if (turns > 2){ //ie 3
        turnLeft();
        turns++;
      }
      else{
        while(turns != 0){
          turnRight();
          turns--;
        }
      }
      //Robot should now be facing up (turns = 0).
      y++;
    }

    else if (route[direction_counter] == 3){   //robot turned right...
      if (turns < 1){ //ie 0
        turnLeft();
        turns++;
      }
      else{
        while(turns != 1){
          turnRight();
          turns--;
        }
      }
      //Robot should now be facing Left (turns = 1).
      x--;
    }

    drive_goto(<BaseSpeed>);    //You know what i mean
    if (turns < 0){
      turns += 4;
    }
    else{
      turns %= 4;
    }

    direction_counter--;

  }//end for loop
}// end function
