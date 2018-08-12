#include "states.h"

static const StateInfo state_infos[6] = {
  {IDLE::setup, IDLE::enter, IDLE::exit, IDLE::loop, IDLE::event},
  {MAGLIFTER::setup, MAGLIFTER::enter, MAGLIFTER::exit, MAGLIFTER::loop, MAGLIFTER::event},
  {POOLSHOT::setup, POOLSHOT::enter, POOLSHOT::exit, POOLSHOT::loop, POOLSHOT::event},
  {PACHINKO::setup, PACHINKO::enter, PACHINKO::exit, PACHINKO::loop, PACHINKO::event},
  {VARIABLEFRICTION::setup, VARIABLEFRICTION::enter, VARIABLEFRICTION::exit, VARIABLEFRICTION::loop, VARIABLEFRICTION::event},
  {TCT::setup, TCT::enter, TCT::exit, TCT::loop, TCT::event}
};

static const WireValue wire_values[18] = {
  {2, 0, sizeof(uint16_t), (Value<void*>*) &POOLSHOT::shooterPosition},
  {2, 1, sizeof(uint8_t), (Value<void*>*) &POOLSHOT::goalNum},
  {2, 2, sizeof(uint8_t), (Value<void*>*) &POOLSHOT::shotResult},
  {2, 3, sizeof(uint16_t), (Value<void*>*) &POOLSHOT::poolScore},
  {2, 4, sizeof(uint16_t), (Value<void*>*) &POOLSHOT::pointCount},
  {2, 5, sizeof(bool), (Value<void*>*) &POOLSHOT::sensor},
  {2, 6, sizeof(uint16_t), (Value<void*>*) &POOLSHOT::totalScore},
  {2, 7, sizeof(uint16_t), (Value<void*>*) &POOLSHOT::count},
  {3, 0, sizeof(uint16_t), (Value<void*>*) &PACHINKO::dropperPos},
  {3, 1, sizeof(uint16_t), (Value<void*>*) &PACHINKO::redScore},
  {3, 2, sizeof(uint16_t), (Value<void*>*) &PACHINKO::blueScore},
  {3, 3, sizeof(uint16_t), (Value<void*>*) &PACHINKO::yellowScore},
  {3, 4, sizeof(bool), (Value<void*>*) &PACHINKO::redSensor},
  {3, 5, sizeof(bool), (Value<void*>*) &PACHINKO::blueSensor},
  {3, 6, sizeof(bool), (Value<void*>*) &PACHINKO::yellowSensor},
  {3, 7, sizeof(uint16_t), (Value<void*>*) &PACHINKO::count},
  {4, 0, sizeof(uint8_t), (Value<void*>*) &VARIABLEFRICTION::laneNum1},
  {4, 1, sizeof(uint8_t), (Value<void*>*) &VARIABLEFRICTION::laneNum2}
};

MasterManager<State, 6, 18> manager(0xd312d0b0, state_infos, wire_values, 7);

namespace IDLE {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace amib4 {

namespace events {

}
}
}
namespace MAGLIFTER {


void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::Left();
    break;
  case 1:
    events::Right();
    break;
  case 2:
    events::cycleBall();
    break;
  case 3:
    events::finishedAction();
    break;
  case 4:
    events::liftPiston();
    break;
  default:
    break;
  }
}

namespace amib4 {

namespace events {

}
}
namespace tablet {

namespace events {
void finishedAction() { manager.sendTabletEvent(0); }
}
}
}
namespace POOLSHOT {
Value<uint16_t> shooterPosition;
Value<uint8_t> goalNum;
Value<uint8_t> shotResult;
Value<uint16_t> poolScore;
Value<uint16_t> pointCount;
Value<bool> sensor;
Value<uint16_t> totalScore;
Value<uint16_t> count;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::testLEDs();
    break;
  case 1:
    events::shootBall();
    break;
  case 2:
    events::liftMechanism();
    break;
  case 3:
    events::homeShooter();
    break;
  case 4:
    events::demo();
    break;
  case 5:
    events::finishedAction();
    break;
  case 6:
    events::ballScored();
    break;
  case 7:
    events::loseGame();
    break;
  case 8:
    events::releasePiston();
    break;
  default:
    break;
  }
}

namespace amib4 {

namespace events {

}
}
namespace tablet {
RemoteValue<0, uint8_t> goalNum(0);
RemoteValue<0, uint8_t> shotResult(1);
RemoteValue<0, uint16_t> blinkLED(2);
RemoteValue<0, uint16_t> poolScore(3);
RemoteValue<0, uint16_t> pointCount(4);
RemoteValue<0, uint16_t> totalScore(5);
RemoteValue<0, uint16_t> count(6);
namespace events {
void finishedAction() { manager.sendTabletEvent(0); }
void ballScored() { manager.sendTabletEvent(1); }
void loseGame() { manager.sendTabletEvent(2); }
}
}
namespace amib2 {
RemoteValue<2, uint16_t> shooterPosition(0);
namespace events {
void shootBall() { manager.sendSlaveEvent(2, 0); }
void testLEDs() { manager.sendSlaveEvent(2, 1); }
void liftMechanism() { manager.sendSlaveEvent(2, 2); }
void homeShooter() { manager.sendSlaveEvent(2, 3); }
void demo() { manager.sendSlaveEvent(2, 4); }
}
}
}
namespace PACHINKO {
Value<uint16_t> dropperPos;
Value<uint16_t> redScore;
Value<uint16_t> blueScore;
Value<uint16_t> yellowScore;
Value<bool> redSensor;
Value<bool> blueSensor;
Value<bool> yellowSensor;
Value<uint16_t> count;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::pumpAndReset();
    break;
  case 1:
    events::releaseBall();
    break;
  case 2:
    events::demo();
    break;
  case 3:
    events::goLeft();
    break;
  case 4:
    events::goRight();
    break;
  case 5:
    events::pachinkoHome();
    break;
  case 6:
    events::ballLoopHome();
    break;
  case 7:
    events::turnRedLEDOn();
    break;
  case 8:
    events::turnRedLEDOff();
    break;
  case 9:
    events::turnBlueLEDOn();
    break;
  case 10:
    events::turnBlueLEDOff();
    break;
  case 11:
    events::turnYellowLEDOn();
    break;
  case 12:
    events::turnYellowLEDOff();
    break;
  case 13:
    events::playPachinko();
    break;
  case 14:
    events::centerSetup();
    break;
  case 15:
    events::dropperSetup();
    break;
  case 16:
    events::ballPumpSetup();
    break;
  case 17:
    events::switchSetup();
    break;
  case 18:
    events::finishedAction();
    break;
  case 19:
    events::loseGame();
    break;
  case 20:
    events::winGame();
    break;
  case 21:
    events::test();
    break;
  case 22:
    events::TCTgame();
    break;
  case 23:
    events::moveOnAction();
    break;
  case 24:
    events::blueSensorOn();
    break;
  default:
    break;
  }
}

namespace amib4 {

namespace events {

}
}
namespace tablet {
RemoteValue<0, uint16_t> redScore(0);
RemoteValue<0, uint16_t> blueScore(1);
RemoteValue<0, uint16_t> yellowScore(2);
RemoteValue<0, uint16_t> count(3);
namespace events {
void ballScored() { manager.sendTabletEvent(0); }
void chooseWhereNext() { manager.sendTabletEvent(1); }
void finishedAction() { manager.sendTabletEvent(2); }
void loseGame() { manager.sendTabletEvent(3); }
void winGame() { manager.sendTabletEvent(4); }
void redCupScored() { manager.sendTabletEvent(5); }
void yellowCupScored() { manager.sendTabletEvent(6); }
void blueCupScored() { manager.sendTabletEvent(7); }
void TCTgame() { manager.sendTabletEvent(8); }
void moveOnAction() { manager.sendTabletEvent(9); }
void blueSensorOn() { manager.sendTabletEvent(10); }
}
}
namespace amib2 {

namespace events {
void turnRedLEDOn() { manager.sendSlaveEvent(2, 0); }
void turnRedLEDOff() { manager.sendSlaveEvent(2, 1); }
void turnBlueLEDOn() { manager.sendSlaveEvent(2, 2); }
void turnBlueLEDOff() { manager.sendSlaveEvent(2, 3); }
void turnYellowLEDOn() { manager.sendSlaveEvent(2, 4); }
void turnYellowLEDOff() { manager.sendSlaveEvent(2, 5); }
void blueSensorOn() { manager.sendSlaveEvent(2, 6); }
}
}
namespace amib3 {
RemoteValue<3, uint16_t> dropperPos(0);
namespace events {
void pumpAndReset() { manager.sendSlaveEvent(3, 0); }
void releaseBall() { manager.sendSlaveEvent(3, 1); }
void demo() { manager.sendSlaveEvent(3, 2); }
void goLeft() { manager.sendSlaveEvent(3, 3); }
void goRight() { manager.sendSlaveEvent(3, 4); }
void pachinkoHome() { manager.sendSlaveEvent(3, 5); }
void ballLoopHome() { manager.sendSlaveEvent(3, 6); }
void playPachinko() { manager.sendSlaveEvent(3, 7); }
void centerSetup() { manager.sendSlaveEvent(3, 8); }
void dropperSetup() { manager.sendSlaveEvent(3, 9); }
void ballPumpSetup() { manager.sendSlaveEvent(3, 10); }
void switchSetup() { manager.sendSlaveEvent(3, 11); }
void test() { manager.sendSlaveEvent(3, 12); }
void finishedAction() { manager.sendSlaveEvent(3, 13); }
}
}
}
namespace VARIABLEFRICTION {
Value<uint8_t> laneNum1;
Value<uint8_t> laneNum2;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::compareTwoLanes();
    break;
  case 1:
    events::compareAll();
    break;
  case 2:
    events::resetRamps();
    break;
  case 3:
    events::sweepBlocks();
    break;
  case 4:
    events::resetSweepers();
    break;
  case 5:
    events::resetBlocks();
    break;
  case 6:
    events::laneThree();
    break;
  default:
    break;
  }
}

namespace amib4 {
RemoteValue<4, uint8_t> laneNum1(0);
RemoteValue<4, uint8_t> laneNum2(1);
namespace events {
void compareTwoLanes() { manager.sendSlaveEvent(4, 0); }
void compareAll() { manager.sendSlaveEvent(4, 1); }
void resetRamps() { manager.sendSlaveEvent(4, 2); }
void sweepBlocks() { manager.sendSlaveEvent(4, 3); }
void resetSweepers() { manager.sendSlaveEvent(4, 4); }
void resetBlocks() { manager.sendSlaveEvent(4, 5); }
void laneThree() { manager.sendSlaveEvent(4, 6); }
}
}
namespace amib3 {
RemoteValue<3, uint8_t> laneNum1(0);
RemoteValue<3, uint8_t> laneNum2(1);
namespace events {
void compareTwoLanes() { manager.sendSlaveEvent(3, 0); }
void compareAll() { manager.sendSlaveEvent(3, 1); }
void resetRamps() { manager.sendSlaveEvent(3, 2); }
}
}
}
namespace TCT {


void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::playTableclothTrick();
    break;
  case 1:
    events::releaseCup();
    break;
  case 2:
    events::pickUp();
    break;
  case 3:
    events::finishedAction();
    break;
  default:
    break;
  }
}

namespace amib4 {

namespace events {

}
}
namespace tablet {

namespace events {
void finishedAction() { manager.sendTabletEvent(0); }
}
}
namespace amib3 {

namespace events {
void playTableclothTrick() { manager.sendSlaveEvent(3, 0); }
void pickUp() { manager.sendSlaveEvent(3, 1); }
void releaseCup() { manager.sendSlaveEvent(3, 2); }
}
}
}

