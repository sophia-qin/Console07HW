#include "FlexyStepper.h"
#include "states.h"
#include <BallPumpStepper.h>
namespace PACHINKO {

// manager.change(SPEEDYSTEPPER.master.values.stepperDirection, -1); 
// NOTE: all of {setup, enter, loop, exit} are optional
   int red = 1; //unsigned integer as indicated in .comm file
   int yellow = 1;
   int blue = 1;
   
   int ballCount = 100;
   
  const byte WALL_PISTON_SENSOR = 29;

void setup() {
  pinMode(WALL_PISTON_SENSOR, INPUT_PULLUP);
  
    Serial3.begin(9600);
}

void enter() {
  // called when state is enteredteppers, etc.
  red = 0; //long unsigned
  yellow = 0;
  blue = 0;
  ballCount = 100;
  count.value = 100;
}

void loop() {
  // called in a loop continuously while in this state
  // monitor sensors, etc.]
  if(count.changed){
    ballCount = count.value;
    count.changed = false;
    Serial3.println(ballCount);
  }
  
  if(!digitalRead(WALL_PISTON_SENSOR)){
    tablet::events::moveOnAction();
    Serial.println("wall sensor sensed");
  }
  
   manager.updateFromSlave(2);
   manager.updateFromSlave(3);
   MANAGER_PASS_ON(tablet, redScore);
   MANAGER_PASS_ON(tablet, yellowScore);
   MANAGER_PASS_ON(tablet, blueScore);
   MANAGER_PASS_ON(amib3, dropperPos);
   
   Serial3.println(redSensor.value);
   Serial3.println(blueSensor.value);
   Serial3.println(yellowSensor.value);
   Serial3.print("count.value: ");
   Serial3.println(count.value);
  
  //lose game if all balls spent and not all goals hit
  if((red == 0 || blue == 0 || yellow == 0) && count.value == 0)
  {
    events::loseGame();
    //events::turnBlueLEDOn();
  }
  
  else if (red != 0 && blue != 0 && yellow != 0)
  {
    tablet::events::winGame();
    //events::turnYellowLEDOn();
  }

  if(redSensor.value) { //value senses something redSensor.value == !digitalRead(redSensor), objects in .comm file have 2 attributes : .changed or .value
   events::turnRedLEDOn(); //calling the event from the master amib
    Serial.println("RedScore");
    red += 10;
    //delay(1000);
    redScore.value = red;
    manager.updateValue(tablet::redScore, redScore.value);
    tablet::events::ballScored(); // tablet::events::ballScored(); , insert in comm file 
    /*
    
    WHEN USING THE UPDATEVALUE FUNCTION YOU NEED TO GIVE IT TWO VALUES. ONE ON ANOTHER AMIB OR TABLET  "tablet::......"
    THEN GIVE IT A VALUE THAT YOU WANT IT TO.
    IT NEEDS TO BE A 
    
    */

    // don't score multiple times
    delay(2000); 
    events::turnRedLEDOff();
    delay (1000);
    redSensor.value = false;
  }
  if(yellowSensor.value) {
    events::turnYellowLEDOn(); //calling the event from the master amib
    Serial.println("YellowScore");
    yellow += 10;
    yellowScore.value = yellow;
    manager.updateValue(tablet::yellowScore, yellowScore.value);
    tablet::events::ballScored();
    delay(2000); 
    events::turnYellowLEDOff();  
    delay(1000);
    yellowSensor.value = false; // fixed double scoring!!, resetting the value
  }
  if(blueSensor.value) {
    events::turnBlueLEDOn(); //calling the event from the master amib
    Serial.println("BlueScore");
    blue += 10;
    blueScore.value = blue;
    manager.updateValue(tablet::blueScore, blueScore.value);
    tablet::events::ballScored();
    delay(2000); 
    events::turnBlueLEDOff(); 
    delay(1000);
    blueSensor.value = false;

  }
}

void events::blueSensorOn(){
  tablet::events::blueSensorOn();
  }

void events::finishedAction(){
  tablet::events::finishedAction();
}

void events::loseGame(){
  tablet::events::loseGame();
  count.value = 100;
}

void events::winGame(){
  tablet::events::winGame();
}

 void events::pumpAndReset() {
   Serial3.println("decrementing!");
   count.value--;
   manager.updateValue(tablet::count, count.value);
 }
 
 void events::releaseBall() {
   amib3::events::releaseBall();
 }
 
 void events::playPachinko() {
   amib3::events::playPachinko();
 }
 
 void events::demo() {
   amib3::events::demo();
 }
 
 void events::goLeft() {
   amib3::events::goLeft();
 }
 
 void events::goRight() {
   amib3::events::goRight();
 }
 
 void events::ballLoopHome() {
   amib3::events::ballLoopHome();
 }
 
 void events::pachinkoHome() {
   amib3::events::pachinkoHome();
 }
 
 void events::turnRedLEDOn() {
  amib2::events::turnRedLEDOn();
  tablet::events::redCupScored();
}

 void events::turnRedLEDOff() {
  amib2::events::turnRedLEDOff();
}

void events::turnBlueLEDOn() {
  amib2::events::turnBlueLEDOn();
  tablet::events::blueCupScored();
}

 void events::turnBlueLEDOff() {
  amib2::events::turnBlueLEDOff();
}

 void events::turnYellowLEDOn() {
  amib2::events::turnYellowLEDOn();
  tablet::events::yellowCupScored();
}
 void events::turnYellowLEDOff() {
  amib2::events::turnYellowLEDOff(); 
}
 void events::dropperSetup() {
  amib3::events::dropperSetup();
}

 void events::switchSetup() {
  amib3::events::switchSetup();
}

 void events::ballPumpSetup() {
  amib3::events::ballPumpSetup();
}

 void events::centerSetup() {
  amib3::events::centerSetup();
}

void events::test() {
  amib3::events::test();
}
 
 void events::TCTgame(){
 tablet::events::TCTgame();
}  
 
void events::moveOnAction(){
  tablet::events::moveOnAction();
}
 
void exit() {
  // called when state is exited
  // disable steppers, let gate up, etc.
}

// now you have to implement the various events


}
