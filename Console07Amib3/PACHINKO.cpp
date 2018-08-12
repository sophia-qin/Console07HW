#include <BallPumpStepper.h>
#include <FlexyStepper.h>
#include <SpeedyStepper.h>
#include "states.h"

namespace PACHINKO {
//NOTE: all of {setup, enter, loop, exit} are optional
//PS = position sensor, HS = homing sensor

//Ball stop to change state
const byte Stop_PS=61;

//electromagnet dropper setup
const byte DROPPER_EM = 9;
const byte DROPPER_STP_PORT = 2; //CHECK
const byte HOMING_STP_LEFT_LS = 24;
const byte HOMING_STP_RIGHT_LS = 25;
const byte FIRST_PISTON = 10;
const byte FIRST_PISTON_SENSOR = A2;
FlexyStepper dropperStp;

//center setup
const byte CENTER_STP_PORT = 3; //port is A1, maybe 3 or 4 for port number?
SpeedyStepper centerStp;

//ball pump setup
const byte BALL_PUMP_STP_PORT = 1;
const byte BALL_PUMP_PS = 8;
const byte BALL_PUMP_HOMING_PS = 23;
const byte BALL_SWITCHER_HS = A1;
const byte BALL_SWITCHER_PS = A0;
const byte BALL_SWITCHER_STP_PORT = 4;
BallPumpStepper ballPump(true); //bool is true if there is a "switcher"

// microstepping: 8x
const float STEPS_PER_MM = 25; 
const float SPEED_IN_MMPS = 50;
const float ACCEL_IN_MMPSPS = 50;
const float MAX_DIST = 268;
const float STEPS_PER_REV = 200;
const float SPEED_IN_REV = 0.5;
const float ACCEL_IN_REV = 0.5;
const float MICROSTEPPING = 8;

unsigned int red = 0; //unsigned integer as indicated in .comm file
unsigned int yellow = 0;
unsigned int blue = 0;

void setup() {
  Serial.begin(9600);
  
  events::dropperSetup();
  Serial.println("dropper");
  digitalWrite(FIRST_PISTON, LOW);
  
  events::centerSetup();
  Serial.println("center");
  
  events::switchSetup();
  Serial.println("switch");
  ballPump.homeSwitch();
  Serial.println("home switch");
  
  events::ballPumpSetup();
  Serial.println("ball pump");
  Serial.println("setup done");
  
  pinMode(Stop_PS, INPUT_PULLUP);
  
  if(!digitalRead(BALL_SWITCHER_HS)) {//only call this function when homed properly (i.e. opening faced downwards)
    Serial.println("sensed");
    ballPump.rotateSwitchToUpPosition();
    Serial.println("up");
  }
  else {
    events::goRight();
    Serial.println("right");
  }
}

 ////////////////////////////////////////EVENTS/////////////////////////////////////////////

 void enter() {//pumps ball up, moves stepper to max dist, and moves switcher left
  Serial.println("enter...");
  dropperStp.enableStepper();
  dropperStp.moveToHomeInMillimeters(1, 50, MAX_DIST + 30, HOMING_STP_LEFT_LS);
  centerStp.enableStepper();
  //ballPump.switchBall(RIGHT);
  //ballPump.homePump();
  Serial.println("enter done");
  }

void loop() {   

  if(dropperPos.changed) {
    digitalWrite(FIRST_PISTON, HIGH);
    analogWrite(DROPPER_EM, 127);
    dropperStp.setTargetPositionInMillimeters((float)dropperPos.value * -1);
    dropperPos.changed = false; //boolean that needs to be set back to false to avoid repeating code
  }
  dropperStp.processMovement();
  /*(if(millis() % 1000 <= 100)
  {
  if(!digitalRead(BALL_PUMP_PS)){
    Serial.println("#triggered");
    events::pachinkoHome();
    ballPump.pumpBall();
    
  }

}
 /*if(digitalRead(Stop_PS) == LOW) {
    master::events::TCTgame();
  } */
}

//dropper stepper and dropper stepper/sensor setup
void events::dropperSetup() {
  pinMode(HOMING_STP_LEFT_LS, INPUT_PULLUP);
  pinMode(HOMING_STP_RIGHT_LS, INPUT_PULLUP);
  pinMode(DROPPER_EM, OUTPUT);
  pinMode(FIRST_PISTON, OUTPUT);
  pinMode(FIRST_PISTON_SENSOR, INPUT_PULLUP);

  dropperStp.connectToPort(DROPPER_STP_PORT);
  dropperStp.enableStepper();
  dropperStp.setStepsPerMillimeter(STEPS_PER_MM*MICROSTEPPING);
  dropperStp.setSpeedInMillimetersPerSecond(SPEED_IN_MMPS);
  dropperStp.setAccelerationInMillimetersPerSecondPerSecond(ACCEL_IN_MMPSPS);
  dropperStp.moveToHomeInMillimeters(1, 25, MAX_DIST + 30, HOMING_STP_LEFT_LS);
  dropperStp.setCurrentPositionInMillimeters(0.0);
}
  
void events::centerSetup() {//center stepper setup
  centerStp.connectToPort(CENTER_STP_PORT);
  centerStp.setStepsPerRevolution(STEPS_PER_REV*MICROSTEPPING*0.75); //fixing math thing
  centerStp.setSpeedInRevolutionsPerSecond(SPEED_IN_REV);
  centerStp.setAccelerationInRevolutionsPerSecondPerSecond(ACCEL_IN_REV);
  centerStp.disableStepper();
}

void events::ballPumpSetup() {//ball pump and ball pump sensor setup
  pinMode(BALL_PUMP_HOMING_PS, INPUT_PULLUP);
  pinMode(BALL_PUMP_PS, INPUT_PULLUP);
  
  ballPump.setPumpIO(BALL_PUMP_STP_PORT, BALL_PUMP_HOMING_PS, BALL_PUMP_PS);
  ballPump.setPumpStepsPerRevolution(STEPS_PER_REV*MICROSTEPPING*5.18);
  ballPump.setPumpSpeedInRPS(SPEED_IN_REV);
  ballPump.setPumpAccInRPSPS(ACCEL_IN_REV);
  ballPump.setPumpDirection(1);
  ballPump.setPumpOffset(0.6);
  
  events::pachinkoHome();
  if(digitalRead(BALL_PUMP_PS) == LOW) {
    ballPump.setupPump();
    ballPump.pumpBall();
    ballPump.homePump();
    events::goRight();
  }
  else{
    ballPump.homePump(1);
  }
}

void events::switchSetup() {//switch and switch sensor setup
  pinMode(BALL_SWITCHER_HS, INPUT_PULLUP);
  pinMode(BALL_SWITCHER_PS, INPUT_PULLUP);
  
  ballPump.setSwitchExists(true);
  ballPump.setSwitchIO(BALL_SWITCHER_STP_PORT, BALL_SWITCHER_HS, BALL_SWITCHER_PS);
  ballPump.setSwitchStepsPerRevolution(STEPS_PER_REV*MICROSTEPPING); 
  ballPump.setSwitchSpeedInRPS(SPEED_IN_REV);
  ballPump.setSwitchAccInRPSPS(ACCEL_IN_REV);
  ballPump.setSwitchTimeout(5000);
  ballPump.setSwitchDirection(1); //1 is set direction
  ballPump.setSwitchPositions(0.40, -0.22);
  ballPump.setSwitchOffset(0.03);
  ballPump.setSwitchUp(0.508);
  ballPump.homeSwitch();
  
  //set up electromagnet, sensors, and piston
  pinMode(HOMING_STP_LEFT_LS, INPUT_PULLUP);
  pinMode(HOMING_STP_RIGHT_LS, INPUT_PULLUP);
  pinMode(DROPPER_EM, OUTPUT);
  pinMode(FIRST_PISTON, OUTPUT);
  pinMode(FIRST_PISTON_SENSOR, INPUT_PULLUP);
  
  //set up cup sensors
  /*pinMode(YELLOW_PS, INPUT_PULLUP);l
  pinMode(RED_PS, INPUT_PULLUP);
  pinMode(BLUE_PS, INPUT_PULLUP);*/
  
  //set up ball pump sensors
  pinMode(BALL_PUMP_HOMING_PS, INPUT_PULLUP);
  pinMode(BALL_PUMP_PS, INPUT_PULLUP);
  pinMode(BALL_SWITCHER_HS, INPUT_PULLUP);
  pinMode(BALL_SWITCHER_PS, INPUT_PULLUP);
  
  //Serial.begin(9600);
}

 ////////////////////////////////////////EVENTS/////////////////////////////////////////////

void events::releaseBall() {//turns off electromagnetic and lights up corresponding leds when sensors are activated
   centerStp.enableStepper();
   centerStp.setupRelativeMoveInRevolutions(5000000);
   analogWrite(DROPPER_EM, 0);
   while(digitalRead(BALL_PUMP_PS)) {
     centerStp.processMovement();
   }
   digitalWrite(FIRST_PISTON, LOW);
   dropperStp.moveToHomeInMillimeters(1, 50, MAX_DIST + 30, HOMING_STP_LEFT_LS); //return home
   events::pumpAndReset();
   centerStp.disableStepper();
   master::events::finishedAction();
  }

void events::demo() {// moves stepper to random position to demo game
  centerStp.enableStepper();
  ballPump.switchBall(RIGHT);
  dropperStp.moveToHomeInMillimeters(1, 50, MAX_DIST + 30, HOMING_STP_LEFT_LS);
  delay(300);
  if(digitalRead(FIRST_PISTON_SENSOR) == LOW) { //when the sensor is activated the electromagnet turns on
    centerStp.setupRelativeMoveInRevolutions(5000000);
    digitalWrite(FIRST_PISTON, HIGH);
    analogWrite(DROPPER_EM, 127);
    int position = (rand() % 268 )* -1;
    dropperStp.setTargetPositionInMillimeters(position);
    while(digitalRead(BALL_PUMP_PS)) { //while the lower sensor is not activated, the electromagnet and center stepper run
      centerStp.processMovement();
      dropperStp.processMovement();
      if(dropperStp.motionComplete()) { //once the electromagnet reaches target, release ball and move piston out
        //delay(300);
        analogWrite(DROPPER_EM, 0);
        //delay(300);
      }
    }
    digitalWrite(FIRST_PISTON, LOW);
    dropperStp.moveToHomeInMillimeters(1, 50, MAX_DIST + 30, HOMING_STP_LEFT_LS); //return home
    centerStp.disableStepper();
    events::pumpAndReset();
   }
   master::events::finishedAction();
  }
  
void events::playPachinko() {// moves stepper to slider position to play game
  if(digitalRead(FIRST_PISTON_SENSOR) == LOW) { //when the sensor is activated the electromagnet turns on
    digitalWrite(FIRST_PISTON, HIGH);
    analogWrite(DROPPER_EM, 127);
  }
}
  
void events::pumpAndReset() {//pumps ball upwards and moves stepper to max dist 
  master::events::pumpAndReset();
  events::pachinkoHome();
  ballPump.setupPump();
  ballPump.pumpBall(); //doesn't pump a full rotation
  //ballPump.homePump(); //not a permanent fix :(
 }

void events::goRight() {//moves switcher right back towards pachinko
  ballPump.switchBall(RIGHT);
 }

void events::goLeft() {//moves switcher right into the ball path
  ballPump.switchBall(LEFT);
 }
 
void events::pachinkoHome() {
  ballPump.homeSwitch();
 }
 
void events::finishedAction(){
}

void events::ballLoopHome() {
  ballPump.rotateSwitchToUpPosition();
 }
 
 void events::test() {
   ballPump.homePump();
   digitalWrite(FIRST_PISTON, HIGH);
   delay(1000);
   digitalWrite(FIRST_PISTON, LOW);
 }

void exit() {
  dropperStp.disableStepper();
  centerStp.disableStepper();
  Serial.println("exit");
 }
 
void reset() {
 }
}