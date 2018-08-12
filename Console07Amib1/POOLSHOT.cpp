#include "states.h"

namespace POOLSHOT {

  const byte WALL_PISTON = 3;
  const byte START_PISTON_SENSOR = 24;
  
  int ballCount = 100;
  
void setup() {
  int count;
  int pointCount;
  
  
  pinMode(WALL_PISTON, OUTPUT);
  pinMode(START_PISTON_SENSOR, INPUT_PULLUP);
  
  pinMode(4, OUTPUT);
  
}

void enter() {
  int count = 0;
  pointCount.value = 0;
  ballCount = 100;
  //count.value = 100;
}

/* id exit() {

} */
void loop() {
  manager.updateFromSlave(2);
  //manager.updateValue(tablet::totalScore, totalScore.value);

  //MANAGER_PASS_ON(tablet, pointCount);
  MANAGER_PASS_ON(amib2, shooterPosition);
  
    if(count.changed){
    ballCount = count.value;
    count.changed = false;
    Serial3.println(ballCount);
  }
  if(count.value == 0)
  {
    events::loseGame();
    //events::turnBlueLEDOn();
  }
  
  if(!digitalRead(START_PISTON_SENSOR)){
    events::finishedAction();
    digitalWrite(4, HIGH);
  }
  
/*  else if (red != 0 && blue != 0 && yellow != 0)
  {
    tablet::events::loseGame();
    //events::turnYellowLEDOn();
  } */
 /* if(sensor.value)
  {
    count += 100;
    pointCount.value = count;
    manager.updateValue(tablet::pointCount, pointCount);
    tablet::events::ballScored();
    sensor.value = false;
  } */
}

void events::releasePiston(){
  digitalWrite(WALL_PISTON, HIGH);
  Serial.println("piston in");
  delay(1000);
  digitalWrite(WALL_PISTON, LOW);
}

void events::testLEDs(){
  amib2::events::testLEDs();
}

void events::shootBall(){
  amib2::events::shootBall();
  count.value--;
  manager.updateValue(tablet::count, count.value);
}

void events::liftMechanism(){
  amib2::events::liftMechanism();
}

void events::homeShooter(){
  amib2::events::homeShooter();
}

void events::demo(){
  amib2::events::demo();
}

void events::finishedAction(){
  tablet::events::finishedAction();
}

void events::loseGame(){
  tablet::events::loseGame();
  count.value = 100;
}
/*
void events::targetBright1Scored(){
  tablet::events::targetBright1Scored();
}

void events::targetBright2Scored(){
  tablet::events::targetBright2Scored();
}
void events::targetBright3Scored(){
  tablet::events::targetBright3Scored();
}
void events::targetBright4Scored(){
  tablet::events::targetBright4Scored();
}
void events::targetBright5Scored(){
  tablet::events::targetBright5Scored();
} */


void events::ballScored(){
  tablet::events::ballScored();
  events::testLEDs();
  
}
}
