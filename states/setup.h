#ifndef __STATES_SETUP_H
#define __STATES_SETUP_H

#include "state.h"
#include "../matrix.h"

class SetupState : public State {
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool SetupState::begin() {
  log("SETUP", "SU");

  Matrix::begin();
  Matrix::print("BT");

  //Serial.begin(BAUDRATE);
  //cloudBegin();
  Bucket::begin();

  return true; //no errors
}

bool SetupState::run() {
  return true; //no errors
}

bool SetupState::isDone() {
	return true;
}

STATE SetupState::nextState() {
  return STATE::READY;
}

#endif
