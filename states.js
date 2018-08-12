
var IDLE = {
  id: 0,
  master: {
    values: {
      
    },
    events: {
      
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_IDLE = 0;
var MAGLIFTER = {
  id: 1,
  master: {
    values: {
      
    },
    events: {
      Left: function Left() { manager.sendEvent(0, 1); },
      Right: function Right() { manager.sendEvent(1, 1); },
      cycleBall: function cycleBall() { manager.sendEvent(2, 1); },
      finishedAction: function finishedAction() { manager.sendEvent(3, 1); },
      liftPiston: function liftPiston() { manager.sendEvent(4, 1); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      finishedAction: new LocalEvent(1, 0)
    }
  }
};
var STATE_MAGLIFTER = 1;
var POOLSHOT = {
  id: 2,
  master: {
    values: {
      shooterPosition: new HardwareValue(2, 0, Manager.TYPE_UINT16),
      goalNum: new HardwareValue(2, 1, Manager.TYPE_UINT8),
      shotResult: new HardwareValue(2, 2, Manager.TYPE_UINT8),
      poolScore: new HardwareValue(2, 3, Manager.TYPE_UINT16),
      pointCount: new HardwareValue(2, 4, Manager.TYPE_UINT16),
      sensor: new HardwareValue(2, 5, Manager.TYPE_BOOL),
      totalScore: new HardwareValue(2, 6, Manager.TYPE_UINT16),
      count: new HardwareValue(2, 7, Manager.TYPE_UINT16)
    },
    events: {
      testLEDs: function testLEDs() { manager.sendEvent(0, 2); },
      shootBall: function shootBall() { manager.sendEvent(1, 2); },
      liftMechanism: function liftMechanism() { manager.sendEvent(2, 2); },
      homeShooter: function homeShooter() { manager.sendEvent(3, 2); },
      demo: function demo() { manager.sendEvent(4, 2); },
      finishedAction: function finishedAction() { manager.sendEvent(5, 2); },
      ballScored: function ballScored() { manager.sendEvent(6, 2); },
      loseGame: function loseGame() { manager.sendEvent(7, 2); },
      releasePiston: function releasePiston() { manager.sendEvent(8, 2); }
    }
  },
  tablet: {
    values: {
      goalNum: new LocalValue(0, Manager.TYPE_UINT8),
      shotResult: new LocalValue(1, Manager.TYPE_UINT8),
      blinkLED: new LocalValue(2, Manager.TYPE_UINT16),
      poolScore: new LocalValue(3, Manager.TYPE_UINT16),
      pointCount: new LocalValue(4, Manager.TYPE_UINT16),
      totalScore: new LocalValue(5, Manager.TYPE_UINT16),
      count: new LocalValue(6, Manager.TYPE_UINT16)
    },
    events: {
      finishedAction: new LocalEvent(2, 0),
      ballScored: new LocalEvent(2, 1),
      loseGame: new LocalEvent(2, 2)
    }
  }
};
var STATE_POOLSHOT = 2;
var PACHINKO = {
  id: 3,
  master: {
    values: {
      dropperPos: new HardwareValue(3, 0, Manager.TYPE_UINT16),
      redScore: new HardwareValue(3, 1, Manager.TYPE_UINT16),
      blueScore: new HardwareValue(3, 2, Manager.TYPE_UINT16),
      yellowScore: new HardwareValue(3, 3, Manager.TYPE_UINT16),
      redSensor: new HardwareValue(3, 4, Manager.TYPE_BOOL),
      blueSensor: new HardwareValue(3, 5, Manager.TYPE_BOOL),
      yellowSensor: new HardwareValue(3, 6, Manager.TYPE_BOOL),
      count: new HardwareValue(3, 7, Manager.TYPE_UINT16)
    },
    events: {
      pumpAndReset: function pumpAndReset() { manager.sendEvent(0, 3); },
      releaseBall: function releaseBall() { manager.sendEvent(1, 3); },
      demo: function demo() { manager.sendEvent(2, 3); },
      goLeft: function goLeft() { manager.sendEvent(3, 3); },
      goRight: function goRight() { manager.sendEvent(4, 3); },
      pachinkoHome: function pachinkoHome() { manager.sendEvent(5, 3); },
      ballLoopHome: function ballLoopHome() { manager.sendEvent(6, 3); },
      turnRedLEDOn: function turnRedLEDOn() { manager.sendEvent(7, 3); },
      turnRedLEDOff: function turnRedLEDOff() { manager.sendEvent(8, 3); },
      turnBlueLEDOn: function turnBlueLEDOn() { manager.sendEvent(9, 3); },
      turnBlueLEDOff: function turnBlueLEDOff() { manager.sendEvent(10, 3); },
      turnYellowLEDOn: function turnYellowLEDOn() { manager.sendEvent(11, 3); },
      turnYellowLEDOff: function turnYellowLEDOff() { manager.sendEvent(12, 3); },
      playPachinko: function playPachinko() { manager.sendEvent(13, 3); },
      centerSetup: function centerSetup() { manager.sendEvent(14, 3); },
      dropperSetup: function dropperSetup() { manager.sendEvent(15, 3); },
      ballPumpSetup: function ballPumpSetup() { manager.sendEvent(16, 3); },
      switchSetup: function switchSetup() { manager.sendEvent(17, 3); },
      finishedAction: function finishedAction() { manager.sendEvent(18, 3); },
      loseGame: function loseGame() { manager.sendEvent(19, 3); },
      winGame: function winGame() { manager.sendEvent(20, 3); },
      test: function test() { manager.sendEvent(21, 3); },
      TCTgame: function TCTgame() { manager.sendEvent(22, 3); },
      moveOnAction: function moveOnAction() { manager.sendEvent(23, 3); },
      blueSensorOn: function blueSensorOn() { manager.sendEvent(24, 3); }
    }
  },
  tablet: {
    values: {
      redScore: new LocalValue(0, Manager.TYPE_UINT16),
      blueScore: new LocalValue(1, Manager.TYPE_UINT16),
      yellowScore: new LocalValue(2, Manager.TYPE_UINT16),
      count: new LocalValue(3, Manager.TYPE_UINT16)
    },
    events: {
      ballScored: new LocalEvent(3, 0),
      chooseWhereNext: new LocalEvent(3, 1),
      finishedAction: new LocalEvent(3, 2),
      loseGame: new LocalEvent(3, 3),
      winGame: new LocalEvent(3, 4),
      redCupScored: new LocalEvent(3, 5),
      yellowCupScored: new LocalEvent(3, 6),
      blueCupScored: new LocalEvent(3, 7),
      TCTgame: new LocalEvent(3, 8),
      moveOnAction: new LocalEvent(3, 9),
      blueSensorOn: new LocalEvent(3, 10)
    }
  }
};
var STATE_PACHINKO = 3;
var VARIABLEFRICTION = {
  id: 4,
  master: {
    values: {
      laneNum1: new HardwareValue(4, 0, Manager.TYPE_UINT8),
      laneNum2: new HardwareValue(4, 1, Manager.TYPE_UINT8)
    },
    events: {
      compareTwoLanes: function compareTwoLanes() { manager.sendEvent(0, 4); },
      compareAll: function compareAll() { manager.sendEvent(1, 4); },
      resetRamps: function resetRamps() { manager.sendEvent(2, 4); },
      sweepBlocks: function sweepBlocks() { manager.sendEvent(3, 4); },
      resetSweepers: function resetSweepers() { manager.sendEvent(4, 4); },
      resetBlocks: function resetBlocks() { manager.sendEvent(5, 4); },
      laneThree: function laneThree() { manager.sendEvent(6, 4); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_VARIABLEFRICTION = 4;
var TCT = {
  id: 5,
  master: {
    values: {
      
    },
    events: {
      playTableclothTrick: function playTableclothTrick() { manager.sendEvent(0, 5); },
      releaseCup: function releaseCup() { manager.sendEvent(1, 5); },
      pickUp: function pickUp() { manager.sendEvent(2, 5); },
      finishedAction: function finishedAction() { manager.sendEvent(3, 5); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      finishedAction: new LocalEvent(5, 0)
    }
  }
};
var STATE_TCT = 5;

var STATES = {
  IDLE: IDLE,
  MAGLIFTER: MAGLIFTER,
  POOLSHOT: POOLSHOT,
  PACHINKO: PACHINKO,
  VARIABLEFRICTION: VARIABLEFRICTION,
  TCT: TCT
};
var manager = new Manager([IDLE, MAGLIFTER, POOLSHOT, PACHINKO, VARIABLEFRICTION, TCT]);
