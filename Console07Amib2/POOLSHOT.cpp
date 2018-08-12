#include "states.h"
#include <Wire.h>
#include <FlexyStepper.h>
#include <I2CServoController.h>
#include <Adafruit_NeoPixel.h>

namespace POOLSHOT {

// NOTE: all of {setup, enter, loop, exit} are optional

int pointCount;
//LEDS from left to right
//const byte holeLED = 28;

//PoolShot Values
//pnuematics
const byte shooterP = 10; //hits/shoots the ball, at front of game
const byte ballRaisingPiston = 3; //front piston on surface
const byte gameOverP = 4; //back piston on surface
const byte anglePiston = 9; //pancake piston? angles entire game back and forth/up and down--resets balls

//sensors
const byte holePS1 = 23;
const byte holePS2 = 24;
const byte holePS3 = 27; //recycle PS
const byte holePS4 = 25;
const byte holePS5 = 26;

const byte holePSarray [5] = { holePS1, holePS2, holePS3, holePS4, holePS5};
//Variables
const byte goals [5] = {
    0, 1, 3, 2, 4};
    
uint8_t whichGoal = 0;
uint8_t numberOfTrys = 3;

const byte shotTime = 500;
const byte waitTime = 500;

const byte STEPS_PER_MM = 25*8; //200*8*48: base steps per revolution * 8 microsteps per step *48:1 gear ratio
const float SPEED_IN_SPS = 400; //0.1
const float ACCEL_IN_SPSPS = 800; //0.1
const float MAX_DIST_IN_S = 6400; //0.111, 1/9 of a revolution
const float HOMING_SPEED_IN_SPS = 400; //0.05

//homing
const byte directionTowardHome = 1; // + 1 moves it toward the sensor - Siena :)
const byte zeroingSensor = 8;

//booleans
bool shooterShot = false;

const byte SHOOTER_PORT = 1;
FlexyStepper shooterMotor;
 
//Neopixel Variables
const int NUMPIXELS = 5;
const byte PIN = 28;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t white = pixels.Color(255, 255, 255);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t off = pixels.Color(0, 0, 0);

uint32_t pixelColorArray[5] = {blue, yellow, red, yellow, blue};
 int score[5] = {0,0,0,0,0};
 int allScore = 0;

void setup()
{ 
  //sensors
  pinMode(holePS1, INPUT_PULLUP);
  pinMode(holePS2, INPUT_PULLUP);
  pinMode(holePS3, INPUT_PULLUP);
  pinMode(holePS4, INPUT_PULLUP);
  pinMode(holePS5, INPUT_PULLUP);
  pinMode(zeroingSensor, INPUT_PULLUP);
  
  //Neopixel
  pixels.begin();
  //pixels.show();
  
  //pnuematics
  pinMode(shooterP, OUTPUT);
  pinMode(ballRaisingPiston, OUTPUT);
  pinMode(gameOverP, OUTPUT);
 
  //stepper
  shooterMotor.connectToPort(SHOOTER_PORT);
  shooterMotor.enableStepper();
  shooterMotor.setSpeedInStepsPerSecond(SPEED_IN_SPS);
  shooterMotor.setAccelerationInStepsPerSecondPerSecond(ACCEL_IN_SPSPS);
  shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
  shooterMotor.disableStepper();
 
  Serial.begin(9600);
  Serial.println("I AM AT SETUP END");
}

//
// initialize the project, this includes setup steps that take time, such as homing a
// stepper motor.
//

void enter(){
  Serial.println("enter");
  shooterMotor.enableStepper();
  shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
   
  pixels.setPixelColor(0, blue);
  pixels.setPixelColor(1, yellow);
  pixels.setPixelColor(2, red);
  pixels.setPixelColor(3, yellow);
  pixels.setPixelColor(4, blue);
  pixels.show();
 
for(int i =0; i<5; i++)
{
  score [i] = 0;
}
allScore = 0;

}

void loop(){
  /*if(shooterShot == true){
      checkForScore(whichGoal);
      digitalWrite(ballRaisingPiston, LOW);
      delay (3000);
      liftMechanism();
      shooterShot = false;

      if (whichGoal >= 5){
        //events::gameOver();
      }

      delay (1000);
      lightUpInitialLED (goals [whichGoal]);
      //Serial.println (light + goals[whichGoal] + white);
  }*/

  if(shooterPosition.changed){
    if(shooterPosition.value > 3200){
      shooterPosition.value = 3200;
    }
    shooterPosition.changed = false;
    shooterMotor.setTargetPositionInSteps((float)shooterPosition.value - 3200);
    Serial.println("hi");
  }
  shooterMotor.processMovement();
  
  /*if(!digitalRead(holePS1)){
    events::targetBright1Scored();
    Serial.println("Target 1 scored");
  }
  
  if(!digitalRead(holePS2)){
    events::targetBright2Scored();
    Serial.println("Target 2 scored");
  }
  
/*  if(!digitalRead(holePS3)){
    events::targetBright3Scored();
    Serial.println("Target 3 scored");
  } */
  
/*  if(!digitalRead(holePS4)){
    events::targetBright4Scored();
    Serial.println("Target 4 Scored");
  }
  
  if(!digitalRead(holePS5)){
    events::targetBright5Scored();
    Serial.println("Target 5 scored");
  }*/
  /*
 for(int index = 0; index < 5; index ++){
   if(!digitalRead(holePSarray[index])){
     pixels.setPixelColor(index, white);
     pixels.show();
     pixels.setPixelColor(index, pixelColorArray[index]);
     pixels.show();
     break;
     
   }
 }
 
 */
  
  
  //Serial.println(allScore);
  //not sure if this is same function as checkForScore
  /*
  if(!digitalRead(holePS1)){
    //send score
     pixels.setPixelColor(0, white);
     pixels.show();
     delay(1000);
     pixels.setPixelColor(0, blue);
     pixels.show();
  }

}
/*

buttons:
cue: liftMechanism()
fire: shootBall()
dial: loop w/ value
goals: neopixels--mimic led code on pachinko
lives: mimic heart setup
*/
}
// now you have to implement the various events
void events::demo() { //demo function for poolshot game
  //shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
  delay(100);
  digitalWrite(shooterP, HIGH);
  delay(100);
  shooterMotor.moveToPositionInSteps(-700); //hits ball straight on, should go into center goal zone
  delay(1000);
  digitalWrite(anglePiston, HIGH);
  delay(1000);
  digitalWrite(gameOverP, HIGH);
  delay(1000);
  digitalWrite(ballRaisingPiston, HIGH);
  delay(2000);
  digitalWrite(shooterP, LOW);
  shooterShot = true;
  delay (1000);
  digitalWrite(ballRaisingPiston, LOW);
  digitalWrite(gameOverP, LOW);
  delay(100);
  digitalWrite(anglePiston, LOW);
  ////////////////////
  digitalWrite(shooterP, HIGH);
  delay(100);
  shooterMotor.moveToPositionInSteps(-900); //hits ball straight on, should go into center goal zone
  delay(1000);
  digitalWrite(anglePiston, HIGH);
  delay(1000);
  digitalWrite(gameOverP, HIGH);
  delay(1000);
  digitalWrite(ballRaisingPiston, HIGH);
  delay(2000);
  digitalWrite(shooterP, LOW);
  shooterShot = true;
  delay (1000);
  digitalWrite(ballRaisingPiston, LOW);
  digitalWrite(gameOverP, LOW);
  delay(100);
  digitalWrite(anglePiston, LOW);
  /////////////////////
  digitalWrite(shooterP, HIGH);
  delay(100);
  shooterMotor.moveToPositionInSteps(-1600); //hits ball straight on, should go into center goal zone
  delay(1000);
  digitalWrite(anglePiston, HIGH);
  delay(1000);
  digitalWrite(gameOverP, HIGH);
  delay(1000);
  digitalWrite(ballRaisingPiston, HIGH);
  delay(2000);
  digitalWrite(shooterP, LOW);
  shooterShot = true;
  delay (1000);
  digitalWrite(ballRaisingPiston, LOW);
  digitalWrite(gameOverP, LOW);
  delay(100);
  digitalWrite(anglePiston, LOW);
  shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
  master::events::finishedAction();
}
/*void events::targetBright1Scored(){
  master::events::targetBright1Scored();
}
void events::targetBright2Scored(){
  master::events::targetBright2Scored();
}
void events::targetBright3Scored(){
  master::events::targetBright3Scored();
}
void events::targetBright4Scored(){
  master::events::targetBright4Scored();
}
void events::targetBright5Scored(){
  master::events::targetBright5Scored();
} */
void events::homeShooter(){
  long directionTowardHome = 1; // + 1 moves it toward the sensor 
  shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
  //shooterMotor.moveToHomeInSteps(1, 2, 50, zeroingSensor);
}

void resetShooter() {
  digitalWrite(ballRaisingPiston, LOW);
  delay(500);
  digitalWrite(gameOverP, LOW);
  delay(100);
  digitalWrite(anglePiston, LOW);
  shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
}

void events::shootBall(){ //"fire" button function: shoots the ball and resets
  digitalWrite(shooterP, LOW);
  shooterShot = true;
  unsigned long currentTime = millis();
  unsigned long shotTimer = 2000;
  unsigned long finishTime = currentTime + shotTimer;
  int pointCount = 0;
  
  
 while(millis() < finishTime) {
  for(int index = 0; index < 5; index ++){
   if(!digitalRead(holePSarray[index])){
     pixels.setPixelColor(index, white);
     pixels.show();
     delay(1000);
     pixels.setPixelColor(index, pixelColorArray[index]);
     pixels.show();
     ///////Add scoring here and UI/////////
     score[index] = 1;
     allScore = score[0] + score [1] + score[2] + score[3] + score[4];
     manager.updateValue(master::totalScore,(uint16_t)allScore);
     Serial.println("ball scored");
     master::events::ballScored();
   }
 } 
 }
  resetShooter();
  master::events::finishedAction();
}



void events::liftMechanism(){ //activated when entering a poolshot game scene--sets the game up
  shooterMotor.moveToHomeInSteps(1, HOMING_SPEED_IN_SPS, MAX_DIST_IN_S, zeroingSensor);
  delay(100);
  digitalWrite(shooterP, HIGH);
  delay(100);
  digitalWrite(anglePiston, HIGH);
  delay(2000);
  digitalWrite(gameOverP, HIGH);
  delay(1000);
  digitalWrite(ballRaisingPiston, HIGH);
  delay(2000);
  master::events::finishedAction();
}

void blinkLED(int index){
    pixels.setPixelColor(index, blue);
    pixels.show();
    delay(1000);
    pixels.setPixelColor(index, yellow);
    pixels.show();
}

//not sure how to convert to event
void checkForScore(int index){
  byte sensorNumbers [5] = {
    holePS1, holePS2, holePS3, holePS4, holePS5};
    
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  long interval = 4000;
  boolean passedSensor = false;
  uint8_t shotResult = 0;
  
  while (currentMillis - previousMillis < interval) {//for 1.5 seconds after shot checks to see if the ball is sensed & blinks that goal blue if it is
  if (!digitalRead(sensorNumbers[index])){
        
      //Serial.print("Score in: ");
      //Serial.println(index);
      passedSensor = true;
      //blinkLED(goals [index], blue);
      whichGoal++;
      //manager.updateValue(master::goalNum, whichGoal);
      shotResult = 1; 
      //manager.updateValue(master::shotResult, shotResult);
      break;
    }
    previousMillis = currentMillis; 
  }
  
  if (passedSensor == false){ //after 1.5 seconds, red LED blinks and stuff happens if ball is not sensed
      numberOfTrys--;
      //blinkLED(goals [index], red);
      shotResult = 0;
      //manager.updateValue(master::shotResult, shotResult);
    }

  if (numberOfTrys <= 0){
    numberOfTrys = 3;
    whichGoal++;   //after failing 3 times you automatically move on to the next goal
    manager.updateValue(master::goalNum, whichGoal);
  }
}


////////////////////////////////////////////PSEUDO CODE////////////////////////////////////////////////////////////////////

void lightUpInitialLED (int index){
  digitalWrite(ballRaisingPiston, HIGH);
  delay (waitTime);
  
  //blinkLED (goals [index], 'w');
}

void events::testLEDs(){
  //pixels.begin();
  pixels.setPixelColor(0, blue);
  pixels.setPixelColor(1, red);
  pixels.setPixelColor(2, blue);
  pixels.setPixelColor(3, red);
  pixels.setPixelColor(4, blue);
  pixels.show();
  //pixels.setPixelColor(0, 255, 255, 255);
  delay(2000);
  pixels.setBrightness(0);
  pixels.show();
  delay(2000);
  pixels.setBrightness(255);
  pixels.show();
  
  delay(2000);
  
  
}

void exit(){
  shooterMotor.disableStepper();
  Serial.println("exit");
}
}

// -------------------------------------- End --------------------------------------

//have values go between ui and hw to signal when user selects
