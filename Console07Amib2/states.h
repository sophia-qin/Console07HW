#pragma once

#define SLAVEMANAGER
#include <Manager.h>

namespace IDLE {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {


namespace events {

}
}
}

namespace MAGLIFTER {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {


namespace events {
void Left();
void Right();
void cycleBall();
void finishedAction();
void liftPiston();
}
}
}

namespace POOLSHOT {
extern Value<uint16_t> shooterPosition;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {
void shootBall();
void testLEDs();
void liftMechanism();
void homeShooter();
void demo();
}

namespace master {
extern RemoteValue<0, uint16_t> shooterPosition;
extern RemoteValue<0, uint8_t> goalNum;
extern RemoteValue<0, uint8_t> shotResult;
extern RemoteValue<0, uint16_t> poolScore;
extern RemoteValue<0, uint16_t> pointCount;
extern RemoteValue<0, bool> sensor;
extern RemoteValue<0, uint16_t> totalScore;
extern RemoteValue<0, uint16_t> count;

namespace events {
void testLEDs();
void shootBall();
void liftMechanism();
void homeShooter();
void demo();
void finishedAction();
void ballScored();
void loseGame();
void releasePiston();
}
}
}

namespace PACHINKO {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {
void turnRedLEDOn();
void turnRedLEDOff();
void turnBlueLEDOn();
void turnBlueLEDOff();
void turnYellowLEDOn();
void turnYellowLEDOff();
void blueSensorOn();
}

namespace master {
extern RemoteValue<0, uint16_t> dropperPos;
extern RemoteValue<0, uint16_t> redScore;
extern RemoteValue<0, uint16_t> blueScore;
extern RemoteValue<0, uint16_t> yellowScore;
extern RemoteValue<0, bool> redSensor;
extern RemoteValue<0, bool> blueSensor;
extern RemoteValue<0, bool> yellowSensor;
extern RemoteValue<0, uint16_t> count;

namespace events {
void pumpAndReset();
void releaseBall();
void demo();
void goLeft();
void goRight();
void pachinkoHome();
void ballLoopHome();
void turnRedLEDOn();
void turnRedLEDOff();
void turnBlueLEDOn();
void turnBlueLEDOff();
void turnYellowLEDOn();
void turnYellowLEDOff();
void playPachinko();
void centerSetup();
void dropperSetup();
void ballPumpSetup();
void switchSetup();
void finishedAction();
void loseGame();
void winGame();
void test();
void TCTgame();
void moveOnAction();
void blueSensorOn();
}
}
}

namespace VARIABLEFRICTION {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {
extern RemoteValue<0, uint8_t> laneNum1;
extern RemoteValue<0, uint8_t> laneNum2;

namespace events {
void compareTwoLanes();
void compareAll();
void resetRamps();
void sweepBlocks();
void resetSweepers();
void resetBlocks();
void laneThree();
}
}
}

namespace TCT {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace events {

}

namespace master {


namespace events {
void playTableclothTrick();
void releaseCup();
void pickUp();
void finishedAction();
}
}
}



enum State {
  STATE_IDLE,
  STATE_MAGLIFTER,
  STATE_POOLSHOT,
  STATE_PACHINKO,
  STATE_VARIABLEFRICTION,
  STATE_TCT
};

extern SlaveManager<State, 6, 1> manager;
