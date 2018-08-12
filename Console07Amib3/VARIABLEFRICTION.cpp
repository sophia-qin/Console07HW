
#include "states.h"
#include <FlexyStepper.h>

namespace VARIABLEFRICTION {

// NOTE: all of {setup, enter, loop, exit} are optional
  /*FlexyStepper stpLane5;

  //steppers chosen in compareLanes event
  FlexyStepper *chosenLane1;
 // FlexyStepper *chosenLane2;

  const byte FRONT_LS_5 = A0;
  const byte HOME_LS_5 = A2;

  const float STEPS_PER_MM = 20;
  const float SPEED_IN_MMPS = 85;
  const float ACCEL_IN_MMPSPS = 500;
  const float MAX_DIST = 460;
  const float MAX_DIST_HOMING = 1500;

  const float RAMP_UP = -475; //highest position of ramps in millimeters

FlexyStepper *rampUp(int laneNum) {
  switch(laneNum) {
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
      case 4:
         break;
      case 5:
         stpLane5.setTargetPositionRelativeInMillimeters(RAMP_UP);
         return &stpLane5;
      default:
         break; 
  }
  return NULL;
}

void setup() {
  // do setup!
  // things like pinMode, configure steppers, etc.
  pinMode(FRONT_LS_5, INPUT_PULLUP);
  pinMode(HOME_LS_5, INPUT_PULLUP);

  stpLane5.connectToPort(4);
  stpLane5.setStepsPerMillimeter(STEPS_PER_MM);
  stpLane5.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  stpLane5.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  stpLane5.disableStepper();
  
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  stpLane5.enableStepper();
  stpLane5.moveToHomeInMillimeters(1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_5);
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
  stpLane5.disableStepper();
 
}
*/
// now you have to implement the various events
void events::compareTwoLanes() {/*
  manager.println("event compareTwoLanes called!");
  chosenLane1 = rampUp(laneNum1);
  chosenLane2 = rampUp(laneNum2);

  if (chosenLane1 != NULL) {
    chosenLane1->setTargetPositionRelativeInMillimeters(RAMP_UP);
  }
  if (chosenLane2 != NULL) {
    chosenLane2->setTargetPositionRelativeInMillimeters(RAMP_UP);
  }
  FlexyStepper *const lanes[2] = {chosenLane1, chosenLane2};
  FlexyStepper::finishAllMovements(2, lanes  );*/
}

void events::compareAll() {/*
  manager.println("event compareAll called!");
  stpLane5.setTargetPositionRelativeInMillimeters(RAMP_UP);
  FlexyStepper::finishAllMovements(1, (FlexyStepper *const[1]) {&stpLane5});*/
}

void events::resetRamps() {/*
  manager.println("event resetRamps called!");
  FlexyHomingSpec homingSpecs[] = {
  FlexyHomingSpec(&stpLane5, 1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_5)
  };
    
  FlexyStepper::homeMultipleInMillimeters(1, homingSpecs);*/
}

}
