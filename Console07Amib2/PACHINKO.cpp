
#include "states.h"

namespace PACHINKO {

// NOTE: all of {setup, enter, loop, exit} are optional

  const byte YELLOW_LED = A7;
  const byte RED_LED = A6;
  const byte BLUE_LED = A5;
  //pachinko goal zones and center setup
  const byte YELLOW_PS = A4;
  const byte RED_PS = A3;
  const byte BLUE_PS = A2;

  
unsigned int red = 0; //unsigned integer as indicated in .comm file
unsigned int yellow = 0;
unsigned int blue = 0;


void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
   
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  red = 0; //long unsigned
  yellow = 0;
  blue = 0;
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
  if (!digitalRead(RED_PS) || !digitalRead(YELLOW_PS) || !digitalRead(BLUE_PS)) {
    manager.updateValue(master::redSensor, !digitalRead(RED_PS)); //updating the value from the master 
    manager.updateValue(master::yellowSensor, !digitalRead(YELLOW_PS)); //send data back to the tablet reporting on results
    manager.updateValue(master::blueSensor, !digitalRead(BLUE_PS));
    delay(1000);
  }
 
  }

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events

void events::blueSensorOn(){
 if(!digitalRead(BLUE_PS)){
  master::events::blueSensorOn(); 
 }
}
void events::turnRedLEDOn() { //turning all of the leds on 
  digitalWrite(RED_LED, HIGH);
}

void events::turnRedLEDOff() { //turning all of the leds off
  digitalWrite(RED_LED, LOW);
}

void events::turnBlueLEDOn() {
  digitalWrite(BLUE_LED, HIGH);
}

void events::turnBlueLEDOff() {
  digitalWrite(BLUE_LED, LOW);
}

void events::turnYellowLEDOn() {
  digitalWrite(YELLOW_LED, HIGH);
}

void events::turnYellowLEDOff() {
  digitalWrite(YELLOW_LED, LOW);
}


}
