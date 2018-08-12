#include <SpeedyStepper.h>
#include <FlexyStepper.h>
#include "states.h"

namespace VARIABLEFRICTION {

// NOTE: all of {setup, enter, loop, exit} are optional 

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
  //MANAGER_PASS_ON(amib3, laneNum1);
 // MANAGER_PASS_ON(amib3, laneNum2);
  //MANAGER_PASS_ON(amib4, laneNum1);
  //MANAGER_PASS_ON(amib4, laneNum2);

}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events
void events::compareTwoLanes(){
  //amib3::events::compareTwoLanes();
  amib4::events::compareTwoLanes();
}

void events::compareAll(){
  //amib3::events::compareAll();
  amib4::events::compareAll();
}

void events::resetRamps(){
  //amib3::events::resetRamps();
  amib4::events::resetRamps();
}

void events::sweepBlocks(){
  amib4::events::sweepBlocks();
}

void events::resetSweepers(){
  amib4::events::resetSweepers();
}

void events::resetBlocks(){
  amib4::events::resetBlocks();
}

void events::laneThree(){
  amib4::events::laneThree();
}

}
