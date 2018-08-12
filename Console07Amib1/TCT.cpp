
#include "states.h"

namespace TCT {

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
   manager.updateFromSlave(3);
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events

void events::playTableclothTrick(){
  amib3::events::playTableclothTrick();
}

void events::pickUp(){
  amib3::events::pickUp();
}

void events::releaseCup(){
  amib3::events::releaseCup();
}

void events::finishedAction(){
  tablet::events::finishedAction();
}

}
