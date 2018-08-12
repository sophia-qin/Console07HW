#include "states.h"

namespace MAGLIFTER {

// NOTE: all of {setup, enter, loop, exit} are optional

  const byte BALL_SWITCHER_HS = A1;
  const byte BALL_SWITCHER_PS = A0;
  unsigned int ballSensed; //no ball = 0, ball = 1

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
  Serial.begin(9600);
  pinMode(BALL_SWITCHER_HS, INPUT_PULLUP);
  pinMode(BALL_SWITCHER_PS, INPUT_PULLUP);
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  ballSensed = 0;
  Serial.println("Enter of maglifter done");
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
 // Serial.println("testing");
 /* if(!digitalRead(BALL_SWITCHER_PS)){
    Serial.println("ball switcher ps sensed");
  } */
  if(!digitalRead(BALL_SWITCHER_HS) && !digitalRead(BALL_SWITCHER_PS)){
   // ballSensed = 1; 
    master::events::finishedAction();
    Serial.println("ball switcher hs sensed");
  }
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events

}
