#include "states.h"
#include <SpeedyStepper.h>
#include <FlexyStepper.h>

//notes - don't forget to add last lane and connect to amib 3. see other notes below 

namespace VARIABLEFRICTION {

// NOTE: all of {setup, enter, loop, exit} are optional

  //sweeper steppers
  FlexyStepper stpSweeperLeft;
  FlexyStepper stpSweeperRight;

  //ramp lane numbers increase from left to right 
  //FlexyStepper stpLane1; 
  FlexyStepper stpLane2;
  FlexyStepper stpLane3;
  FlexyStepper stpLane4;
  //FlexyStepper stpLane5;

  //steppers chosen in compareLanes event
  FlexyStepper *chosenLane3;
  FlexyStepper *chosenLane2; 

  //set to 8x microstepping
  const float STEPS_PER_MM = 20;
  const float SPEED_IN_MMPS = 100;
  const float ACCEL_IN_MMPSPS = 1300;
  const float MAX_DIST = 460;
  const float MAX_DIST_HOMING = 5000;

  const float RAMP_UP = -375; //highest position of ramps in millimeters -475

  const float SWEEPER_END_POSITION = 3280; //position for sweepers after being homed

  const byte SWEEPER_LEFT_FRONT_LS = 8;
  const byte SWEEPER_LEFT_BACK_LS = 25;
  const byte SWEEPER_RIGHT_FRONT_LS = 23;
  const byte SWEEPER_RIGHT_BACK_LS = 24;

  //const byte HOME_LS_1 = A4;
  const byte HOME_LS_2 = A5;
  const byte HOME_LS_3 = A6;
  const byte HOME_LS_4 = A7;
  //const byte HOME_LS_5 = //INSERT;

 // const byte FRONT_LS_1 = 26;
  const byte FRONT_LS_2 = 27;
  const byte FRONT_LS_3 = 28;
  const byte FRONT_LS_4 = 29;
  //const byte FRONT_LS_5 = //INSERT;

  const byte LS_PINS[6] = {
    //HOME_LS_1,
    HOME_LS_2,
    HOME_LS_3,
    HOME_LS_4,
    //HOME_LS_5,
    //FRONT_LS_1,
    FRONT_LS_2,
    FRONT_LS_3,
    FRONT_LS_4,
    //FRONT_LS_5,
    //SWEEPER_LEFT_FRONT_LS,
    //SWEEPER_LEFT_BACK_LS,
    //SWEEPER_RIGHT_FRONT_LS,
    //SWEEPER_RIGHT_BACK_LS
};

FlexyStepper *rampUp(int laneNum){
  switch(laneNum) {
      case 1:
         //stpLane1.setTargetPositionRelativeInMillimeters(RAMP_UP);
         //return &stpLane1;
      case 2:
         stpLane2.setTargetPositionRelativeInMillimeters(RAMP_UP);
         return &stpLane2;
      case 3:
         stpLane3.setTargetPositionRelativeInMillimeters(RAMP_UP);
         return &stpLane3;
      case 4:
         stpLane4.setTargetPositionRelativeInMillimeters(RAMP_UP);
         return &stpLane4;
      /*case 5:
         stpLane5.setTargetPositionRelativeInMillimeters(RAMP_UP);
         return &stpLane5; */
      case 6:
         break;
      default:
         break; 
  }
  return NULL;
}

void events::resetSweepers(){
  FlexyHomingSpec homingSpecs1[] = {
  FlexyHomingSpec(&stpSweeperLeft, -1, STEPS_PER_MM*4, MAX_DIST_HOMING, SWEEPER_LEFT_BACK_LS),
  FlexyHomingSpec(&stpSweeperRight, -1, STEPS_PER_MM*4, MAX_DIST_HOMING, SWEEPER_RIGHT_BACK_LS)
  };
  delay(1000);
  FlexyStepper::homeMultipleInMillimeters(2, homingSpecs1);
}

void events::resetBlocks(){
  stpSweeperLeft.setTargetPositionRelativeInMillimeters(SWEEPER_END_POSITION);
  stpSweeperRight.setTargetPositionRelativeInMillimeters(SWEEPER_END_POSITION);
  FlexyStepper::finishAllMovements(2, (FlexyStepper *const[2]) {&stpSweeperLeft,&stpSweeperRight});
}

void events::resetRamps(){
  FlexyHomingSpec homingSpecs[] = {
  //FlexyHomingSpec(&stpLane1, 1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_1),
  //FlexyHomingSpec(&stpLane2, 1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_2),
  FlexyHomingSpec(&stpLane3, 1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_3),
 // FlexyHomingSpec(&stpLane4, 1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_4) //INSERT COMMA WHEN LANE 5 IS ADDED IN
  //FlexyHomingSpec(&stpLane5, 1, STEPS_PER_MM, MAX_DIST_HOMING, HOME_LS_5)
  };
    
  FlexyStepper::homeMultipleInMillimeters(3, homingSpecs);
}

void setup() {
  Serial.begin(9600);
  // do setup!
  // things like pinMode, configure steppers, etc.
  
  pinMode(FRONT_LS_3, INPUT_PULLUP);
  pinMode(HOME_LS_3, INPUT_PULLUP);
  //pinMode(BBS_1_EMITTER, OUTPUT);
  //pinMode(BBS_1_DETECTOR, INPUT_PULLUP);
  //pinMode(BBS_2_EMITTER, OUTPUT);
  //pinMode(BBS_2_DETECTOR, INPUT_PULLUP);
  //pinMode(BBS_3_EMITTER, OUTPUT);
  //pinMode(BBS_3_DETECTOR, INPUT_PULLUP);
  //pinMode(BBS_4_EMITTER, OUTPUT);
  //pinMode(BBS_4_DETECTOR, INPUT_PULLUP);
  //pinMode(BBS_5_EMITTER, OUTPUT);
  //pinMode(BBS_5_DETECTOR, INPUT_PULLUP);
  
 for (byte i = 0; i < 6; i++) {
    pinMode(LS_PINS[i], INPUT_PULLUP);
  }
  
  //stpSweeperLeft.connectToPort(1);
  //stpSweeperLeft.setStepsPerMillimeter(STEPS_PER_MM);
  //stpSweeperLeft.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS*4);
  //stpSweeperLeft.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  //stpSweeperLeft.disableStepper();
  
  //stpSweeperRight.connectToPort(2);
  //stpSweeperRight.setStepsPerMillimeter(STEPS_PER_MM);
  //stpSweeperRight.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS*4);
  //stpSweeperRight.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  //stpSweeperRight.disableStepper();
  
  /*stpLane1.connectToPort(2);
  stpLane1.setStepsPerMillimeter(STEPS_PER_MM);
  stpLane1.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  stpLane1.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  stpLane1.disableStepper();
  
  
  stpLane2.connectToPort(6);
  stpLane2.setStepsPerMillimeter(STEPS_PER_MM);
  stpLane2.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  stpLane2.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  stpLane2.disableStepper();
  */
  
  stpLane3.connectToPort(5);
  stpLane3.setStepsPerMillimeter(STEPS_PER_MM);
  stpLane3.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  stpLane3.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  stpLane3.disableStepper();
  
  /*
  stpLane4.connectToPort(3);
  stpLane4.setStepsPerMillimeter(STEPS_PER_MM);
  stpLane4.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  stpLane4.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  stpLane4.disableStepper();
  
  stpLane5.connectToPort(//INSERT);
  stpLane5.setStepsPerMillimeter(STEPS_PER_MM);
  stpLane5.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  stpLane5.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  stpLane5.disableStepper();*/
}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  //stpSweeperLeft.enableStepper();
  //stpSweeperRight.enableStepper(); 

  //stpLane1.enableStepper();
  stpLane2.enableStepper();
  stpLane3.enableStepper();
  stpLane4.enableStepper();
  //stpLane5.enableStepper();

 

  //void events::resetRamps();
  //resetSweepers();
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc. 
  
}

void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
  // stpLane1.disableStepper();
  stpLane2.disableStepper();
  stpLane3.disableStepper();
  stpLane4.disableStepper();
  // stpLane5.disableStepper();

  //void events::resetRamps();
  //resetSweepers(); 
}


// now you have to implement the various events

void events::compareTwoLanes() {
  manager.println("event compareTwoLanes called!");
  chosenLane2 = rampUp(2);
  chosenLane3 = rampUp(3);

  //if (chosenLane2 != NULL) move bracket back to original spot     //lane 1
  {
    //chosenLane2->setTargetPositionRelativeInMillimeters(RAMP_UP);
    //if (FRONT_LS_2 =)//add limit switch for both
  }
  if (chosenLane3 != NULL) {
    chosenLane3->setTargetPositionRelativeInMillimeters(RAMP_UP);
  }
  FlexyStepper *const lanes[1] = {chosenLane3}; //chosenLane2
  FlexyStepper::finishAllMovements(1, lanes);
}


void events::compareAll() {
  manager.println("event compareAll called!");
  //stpLane1.setTargetPositionInMillimeters(RAMP_UP);
  stpLane2.setTargetPositionInMillimeters(RAMP_UP);
  stpLane3.setTargetPositionInMillimeters(RAMP_UP);
  stpLane4.setTargetPositionInMillimeters(RAMP_UP);
  //stpLane5.setTargetPositionInMillimeters(RAMP_UP);
  FlexyStepper::finishAllMovements(3, (FlexyStepper *const[3]) {&stpLane2,&stpLane3,&stpLane4});
}

void events::sweepBlocks(){
  //manager.println("event sweepBlocks called!");
  //resetBlocks();  


//void events::resetSweepers(){
  //resetSweepers();
}


void events::laneThree() {
  stpLane3.enableStepper();
  stpLane3.setTargetPositionInMillimeters(RAMP_UP);
  Serial.println("event called");
  while(digitalRead(FRONT_LS_3) == true) {
    Serial.println(digitalRead(FRONT_LS_3));
    stpLane3.processMovement();
  }
  stpLane3.disableStepper();
}


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//if(1_EMITTER = TRIGGERED;)