#include <SerialSlave.h>
#include "states.h"

static const StateInfo state_infos[6] = {
  {IDLE::setup, IDLE::enter, IDLE::exit, IDLE::loop, IDLE::event},
  {MAGLIFTER::setup, MAGLIFTER::enter, MAGLIFTER::exit, MAGLIFTER::loop, MAGLIFTER::event},
  {POOLSHOT::setup, POOLSHOT::enter, POOLSHOT::exit, POOLSHOT::loop, POOLSHOT::event},
  {PACHINKO::setup, PACHINKO::enter, PACHINKO::exit, PACHINKO::loop, PACHINKO::event},
  {VARIABLEFRICTION::setup, VARIABLEFRICTION::enter, VARIABLEFRICTION::exit, VARIABLEFRICTION::loop, VARIABLEFRICTION::event},
  {TCT::setup, TCT::enter, TCT::exit, TCT::loop, TCT::event}
};

static const WireValue wire_values[3] = {
  {3, 0, sizeof(uint16_t), (Value<void*>*) &PACHINKO::dropperPos},
  {4, 0, sizeof(uint8_t), (Value<void*>*) &VARIABLEFRICTION::laneNum1},
  {4, 1, sizeof(uint8_t), (Value<void*>*) &VARIABLEFRICTION::laneNum2}
};

SlaveManager<State, 6, 3> manager(3, state_infos, wire_values);

namespace IDLE {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {


namespace events {

}
}
}
namespace MAGLIFTER {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {


namespace events {
void Left() { manager.sendEvent(0); }
void Right() { manager.sendEvent(1); }
void cycleBall() { manager.sendEvent(2); }
void finishedAction() { manager.sendEvent(3); }
void liftPiston() { manager.sendEvent(4); }
}
}
}
namespace POOLSHOT {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint16_t> shooterPosition(0);
RemoteValue<0, uint8_t> goalNum(1);
RemoteValue<0, uint8_t> shotResult(2);
RemoteValue<0, uint16_t> poolScore(3);
RemoteValue<0, uint16_t> pointCount(4);
RemoteValue<0, bool> sensor(5);
RemoteValue<0, uint16_t> totalScore(6);
RemoteValue<0, uint16_t> count(7);

namespace events {
void testLEDs() { manager.sendEvent(0); }
void shootBall() { manager.sendEvent(1); }
void liftMechanism() { manager.sendEvent(2); }
void homeShooter() { manager.sendEvent(3); }
void demo() { manager.sendEvent(4); }
void finishedAction() { manager.sendEvent(5); }
void ballScored() { manager.sendEvent(6); }
void loseGame() { manager.sendEvent(7); }
void releasePiston() { manager.sendEvent(8); }
}
}
}
namespace PACHINKO {
Value<uint16_t> dropperPos;

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
    events::playPachinko();
    break;
  case 8:
    events::centerSetup();
    break;
  case 9:
    events::dropperSetup();
    break;
  case 10:
    events::ballPumpSetup();
    break;
  case 11:
    events::switchSetup();
    break;
  case 12:
    events::test();
    break;
  case 13:
    events::finishedAction();
    break;
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint16_t> dropperPos(0);
RemoteValue<0, uint16_t> redScore(1);
RemoteValue<0, uint16_t> blueScore(2);
RemoteValue<0, uint16_t> yellowScore(3);
RemoteValue<0, bool> redSensor(4);
RemoteValue<0, bool> blueSensor(5);
RemoteValue<0, bool> yellowSensor(6);
RemoteValue<0, uint16_t> count(7);

namespace events {
void pumpAndReset() { manager.sendEvent(0); }
void releaseBall() { manager.sendEvent(1); }
void demo() { manager.sendEvent(2); }
void goLeft() { manager.sendEvent(3); }
void goRight() { manager.sendEvent(4); }
void pachinkoHome() { manager.sendEvent(5); }
void ballLoopHome() { manager.sendEvent(6); }
void turnRedLEDOn() { manager.sendEvent(7); }
void turnRedLEDOff() { manager.sendEvent(8); }
void turnBlueLEDOn() { manager.sendEvent(9); }
void turnBlueLEDOff() { manager.sendEvent(10); }
void turnYellowLEDOn() { manager.sendEvent(11); }
void turnYellowLEDOff() { manager.sendEvent(12); }
void playPachinko() { manager.sendEvent(13); }
void centerSetup() { manager.sendEvent(14); }
void dropperSetup() { manager.sendEvent(15); }
void ballPumpSetup() { manager.sendEvent(16); }
void switchSetup() { manager.sendEvent(17); }
void finishedAction() { manager.sendEvent(18); }
void loseGame() { manager.sendEvent(19); }
void winGame() { manager.sendEvent(20); }
void test() { manager.sendEvent(21); }
void TCTgame() { manager.sendEvent(22); }
void moveOnAction() { manager.sendEvent(23); }
void blueSensorOn() { manager.sendEvent(24); }
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
  default:
    break;
  }
}

namespace master {
RemoteValue<0, uint8_t> laneNum1(0);
RemoteValue<0, uint8_t> laneNum2(1);

namespace events {
void compareTwoLanes() { manager.sendEvent(0); }
void compareAll() { manager.sendEvent(1); }
void resetRamps() { manager.sendEvent(2); }
void sweepBlocks() { manager.sendEvent(3); }
void resetSweepers() { manager.sendEvent(4); }
void resetBlocks() { manager.sendEvent(5); }
void laneThree() { manager.sendEvent(6); }
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
    events::pickUp();
    break;
  case 2:
    events::releaseCup();
    break;
  default:
    break;
  }
}

namespace master {


namespace events {
void playTableclothTrick() { manager.sendEvent(0); }
void releaseCup() { manager.sendEvent(1); }
void pickUp() { manager.sendEvent(2); }
void finishedAction() { manager.sendEvent(3); }
}
}
}


SLAVERECV
