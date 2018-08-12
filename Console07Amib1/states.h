#pragma once

#include <Manager.h>

namespace IDLE {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib4 {

namespace events {

}
}

namespace events {

}
}

namespace MAGLIFTER {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib4 {

namespace events {

}
}
namespace tablet {

namespace events {
void finishedAction();

}
}

namespace events {
void Left();
void Right();
void cycleBall();
void finishedAction();
void liftPiston();
}
}

namespace POOLSHOT {
extern Value<uint16_t> shooterPosition;
extern Value<uint8_t> goalNum;
extern Value<uint8_t> shotResult;
extern Value<uint16_t> poolScore;
extern Value<uint16_t> pointCount;
extern Value<bool> sensor;
extern Value<uint16_t> totalScore;
extern Value<uint16_t> count;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib4 {

namespace events {

}
}
namespace tablet {
extern RemoteValue<0, uint8_t> goalNum;
extern RemoteValue<0, uint8_t> shotResult;
extern RemoteValue<0, uint16_t> blinkLED;
extern RemoteValue<0, uint16_t> poolScore;
extern RemoteValue<0, uint16_t> pointCount;
extern RemoteValue<0, uint16_t> totalScore;
extern RemoteValue<0, uint16_t> count;
namespace events {
void finishedAction();

void ballScored();

void loseGame();

}
}
namespace amib2 {
extern RemoteValue<2, uint16_t> shooterPosition;
namespace events {
void shootBall();

void testLEDs();

void liftMechanism();

void homeShooter();

void demo();

}
}

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

namespace PACHINKO {
extern Value<uint16_t> dropperPos;
extern Value<uint16_t> redScore;
extern Value<uint16_t> blueScore;
extern Value<uint16_t> yellowScore;
extern Value<bool> redSensor;
extern Value<bool> blueSensor;
extern Value<bool> yellowSensor;
extern Value<uint16_t> count;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib4 {

namespace events {

}
}
namespace tablet {
extern RemoteValue<0, uint16_t> redScore;
extern RemoteValue<0, uint16_t> blueScore;
extern RemoteValue<0, uint16_t> yellowScore;
extern RemoteValue<0, uint16_t> count;
namespace events {
void ballScored();

void chooseWhereNext();

void finishedAction();

void loseGame();

void winGame();

void redCupScored();

void yellowCupScored();

void blueCupScored();

void TCTgame();

void moveOnAction();

void blueSensorOn();

}
}
namespace amib2 {

namespace events {
void turnRedLEDOn();

void turnRedLEDOff();

void turnBlueLEDOn();

void turnBlueLEDOff();

void turnYellowLEDOn();

void turnYellowLEDOff();

void blueSensorOn();

}
}
namespace amib3 {
extern RemoteValue<3, uint16_t> dropperPos;
namespace events {
void pumpAndReset();

void releaseBall();

void demo();

void goLeft();

void goRight();

void pachinkoHome();

void ballLoopHome();

void playPachinko();

void centerSetup();

void dropperSetup();

void ballPumpSetup();

void switchSetup();

void test();

void finishedAction();

}
}

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

namespace VARIABLEFRICTION {
extern Value<uint8_t> laneNum1;
extern Value<uint8_t> laneNum2;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib4 {
extern RemoteValue<4, uint8_t> laneNum1;
extern RemoteValue<4, uint8_t> laneNum2;
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
namespace amib3 {
extern RemoteValue<3, uint8_t> laneNum1;
extern RemoteValue<3, uint8_t> laneNum2;
namespace events {
void compareTwoLanes();

void compareAll();

void resetRamps();

}
}

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

namespace TCT {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace amib4 {

namespace events {

}
}
namespace tablet {

namespace events {
void finishedAction();

}
}
namespace amib3 {

namespace events {
void playTableclothTrick();

void pickUp();

void releaseCup();

}
}

namespace events {
void playTableclothTrick();
void releaseCup();
void pickUp();
void finishedAction();
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

extern MasterManager<State, 6, 18> manager;
