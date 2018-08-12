#include <Arduino.h>
#include <Wire.h>
#include <MultiInterfaceBoard.h>
#include <SpeedyStepper.h>

#include <FlexyStepper.h>

#include "states.h"
#include <Manager.h>
void setup() {
  setupMultiInterfaceBoard();
  manager.setup(STATE_IDLE, &Serial, &Serial3);
  pinMode (10, OUTPUT);
  analogWrite(10, 250);
}

void loop() {
  manager.loop();
}
