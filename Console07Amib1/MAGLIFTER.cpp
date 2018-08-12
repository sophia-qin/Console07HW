
#include "states.h"
#include "FlexyStepper.h"
#include <BallPumpStepper.h>

//The maglifter is the blue and red mechanism on the left side of the console.It uses pneumatics and magnets to move the ball up (hence lifter)

namespace MAGLIFTER {

// NOTE: all of {setup, enter, loop, exit} are optional
//set variables
int waitTime = 900; 

const byte PROXIMITY_SENSOR = 8;

const byte WALL_PISTON_SENSOR = 61;

const byte WALL_PISTON = 3;

const byte AIR_PISTON = 4;

const byte BALL_LIFTER_PS = 24;

const byte BALL_LIFTER = 9;

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
    pinMode(PROXIMITY_SENSOR, INPUT_PULLUP);
    pinMode(WALL_PISTON_SENSOR, INPUT_PULLUP);
    pinMode(WALL_PISTON, OUTPUT);
    pinMode(AIR_PISTON, OUTPUT);
    pinMode(BALL_LIFTER, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(BALL_LIFTER_PS, INPUT_PULLUP);
}

//reset
void reset (){
  digitalWrite(AIR_PISTON, LOW);
}

void firePiston(){
  //Make the red side go up
  digitalWrite(AIR_PISTON, HIGH);
}

void retractPiston(){
  //Retracts the red side
  digitalWrite(AIR_PISTON, LOW);
}
  
void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  //reset();

}

void loop() {
  //When the initial ball lifter senses a ball, then it will raise the ball up
  //When the proximity sensor senses a ball, start cycleBall...brings ball up the maglifter
  //When the ball pump top sensor senses the ball, turn left to complete the ball cycle
  //using maglifter to run the ball loop for now, but later we will have it able to run through multiple states
  
  //using if statements to do a rudimentary form of ball checking
  
  manager.updateFromSlave(3);
  
  /*if (!digitalRead(BALL_LIFTER_PS) ) {
   digitalWrite(BALL_LIFTER, HIGH);
   delay(waitTime*2);
   digitalWrite(BALL_LIFTER, LOW);
  }*/
  //events::maglifterFinished();
  /*
  if (digitalRead(PROXIMITY_SENSOR) == LOW) {
   events::cycleBall();   
  }
  
  
  if (!digitalRead(WALL_PISTON_SENSOR)) {
   digitalWrite(WALL_PISTON, HIGH);
   delay(waitTime*2);
   digitalWrite(WALL_PISTON, LOW);  
  }
  */
  /* if(ballSensed.changed){
    if(ballSensed == 1){
      //do something
    }

  }
  void events::ballSensed(){
  tablet::events::ballSensed();
}
=======
  } */

}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
  //reset();
  retractPiston();
}

// now you have to implement the various events

//red shifts
void events::Left(){
  manager.println("event Left called!");
  firePiston();
}

 //blue shifts
void events::Right(){
  manager.println("event Right called!");
  retractPiston();
}

/*void events::liftBall()
{
  if(!digitalRead(BALL_LIFTER_PS))
  {
    digitalWrite(BALL_LIFTER, HIGH);
   delay(waitTime*2);
   digitalWrite(BALL_LIFTER, LOW);
   delay(waitTime*2);
  }
}
*/

void events::liftPiston(){
  //if(!digitalRead(BALL_LIFTER_PS)){
  digitalWrite(BALL_LIFTER, HIGH);
  delay(waitTime*2);
  digitalWrite(BALL_LIFTER, LOW);
  delay(waitTime*2);
  //}
}
  


void events::cycleBall(){
  //Moves the ball through the maglifter
  manager.println("event cycleBall called!");
  
  for (int x =0; x <7; x++) {
    firePiston();
    delay(waitTime*1.5);
    retractPiston();
    delay(waitTime*1.5);
  } 
}

void events::finishedAction(){
  tablet::events::finishedAction();
  //events::Right();
}
}