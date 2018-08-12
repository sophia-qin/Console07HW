#include "states.h"
#include "SpeedyStepper.h"
#include "RCServo.h"

namespace TCT {
  
#include <Arduino.h>
#include <Wire.h>
#include <SpeedyStepper.h>
#include <MultiInterfaceBoard.h>
#include <RCServo.h>

// There are 5 steppers running off AMIB 3 Define them all so that we can 
// disable all of the ports
SpeedyStepper BS_low; //Port 1
SpeedyStepper P_lead; // Port 2
SpeedyStepper S_Port4; // Port 4
SpeedyStepper TT_stepper; // Port 5
RCServo Claw;


const byte Pin_Home_B=58;
const byte Pin_Home_S=59;
const byte Rset_pin=49; // This is the common AMIB push button pin
int TT_Count=2; // A dummy variable we might need to do state control
const byte Lifter_Pin=3;
const byte Claw_pin=60;

void runTableclothTrick(){
//    if(TT_Count==0)
//  {
    TT_stepper.enableStepper();
    delay(1000);
    Claw.setServoPosition(1);
    delay(1000);
    digitalWrite(Lifter_Pin, HIGH);
    delay(1000);

    TT_stepper.moveToHomeInRevolutions(1, 6, 80, Pin_Home_B);
    delay(1000); // load the cup by hand
    Claw.setServoPosition(-1);
     //   digitalWrite(Lifter_Pin, HIGH);
     delay(1000);
        
    //Move off to home
    TT_stepper.setupRelativeMoveInRevolutions(-42);  
    
    while(!TT_stepper.motionComplete() )
    {
      TT_stepper.processMovement();
    }
    delay(3000); // Show the cup off to the side

    
    TT_stepper.setupRelativeMoveInRevolutions(52); // Drop the cup 
      while(!TT_stepper.motionComplete() )
    {
      TT_stepper.processMovement();
    }
  // Think this should now be donezo
    digitalWrite(Lifter_Pin, LOW);
    
    Claw.setServoPosition(-1);
    TT_stepper.disableStepper(); // Turn off the stepper
    TT_Count=1; // Disable this stater
      
//  }
//  if(digitalRead(Rset_pin) == LOW)
//  {
//    TT_Count=0;
//  }

}
void setup() {
  setupMultiInterfaceBoard();

  // Connect the steppers
  BS_low.connectToPort(1);
  P_lead.connectToPort(2);
  S_Port4.connectToPort(4);
  TT_stepper.connectToPort(5);

  Claw.connectToPin(Claw_pin);
  Claw.setServoPosition(-1);

// Only setting up the stuff for the TC trick
  TT_stepper.setStepsPerRevolution(200*8);
  TT_stepper.setSpeedInRevolutionsPerSecond(6);
  TT_stepper.setAccelerationInRevolutionsPerSecondPerSecond(6);

  pinMode(Pin_Home_B, INPUT_PULLUP);
  pinMode(Pin_Home_S, INPUT_PULLUP);
  pinMode(Rset_pin, INPUT_PULLUP);
  pinMode(Lifter_Pin, OUTPUT);
  digitalWrite(Lifter_Pin, LOW);

}

void enter() {
  // called when state is entered
  // turn on steppers, maybe home steppers, etc.
  TT_stepper.enableStepper();
  BS_low.enableStepper();
  P_lead.enableStepper();
  S_Port4.enableStepper();
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.
  
}

void exit() {
  TT_stepper.disableStepper();
  BS_low.disableStepper();
  P_lead.disableStepper();
  S_Port4.disableStepper();
  TT_stepper.moveToHomeInRevolutions(1, 6, 80, Pin_Home_B);
}

void events::playTableclothTrick() {
  manager.println("event playTableclothTrick called!");
  runTableclothTrick();
  master::events::finishedAction();
}

void events::pickUp() {
  TT_stepper.enableStepper();
  delay(1000);
  Claw.setServoPosition(1);
  delay(1000);
  digitalWrite(Lifter_Pin, HIGH);
  delay(1000);
  TT_stepper.moveToHomeInRevolutions(1, 6, 80, Pin_Home_B);
  delay(1000); // load the cup by hand
  Claw.setServoPosition(-1);
  //digitalWrite(Lifter_Pin, HIGH);
  delay(1000);
  master::events::finishedAction();
}

void events::releaseCup() {
  //Move off to home
  TT_stepper.setupRelativeMoveInRevolutions(-42);  
    
  while(!TT_stepper.motionComplete() )
  {
    TT_stepper.processMovement();
  }
  delay(3000); // Show the cup off to the side

    
  TT_stepper.setupRelativeMoveInRevolutions(52); // Drop the cup 
  while(!TT_stepper.motionComplete() )
  {
    TT_stepper.processMovement();
  }
  //think this should now be donezo
  digitalWrite(Lifter_Pin, LOW);
    
  Claw.setServoPosition(-1);
  TT_stepper.disableStepper(); // Turn off the stepper
  TT_Count=1; // Disable this stater
  master::events::finishedAction();
}


}
