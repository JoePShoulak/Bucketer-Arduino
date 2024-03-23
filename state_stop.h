#ifndef __STATES_STOP_H
#define __STATES_STOP_H

#include "state.h"

class StopState : public State {
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool StopState::begin() {
  log("STOP", "ST");
  return true; //no errors
}

bool StopState::run() {
  return true; //no errors
}

bool StopState::isDone() {
	return true;
}

STATE StopState::nextState() {
  return STATE::READY;
}

#endif
