#ifndef __STATES_READY_H
#define __STATES_READY_H

#include "state.h"

class ReadyState : public State
{
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool ReadyState::begin()
{
  log("READY", "RD");
  return true; // no errors
}

bool ReadyState::run()
{
  return true; // no errors
}

bool ReadyState::isDone()
{
  return true;
}

STATE ReadyState::nextState()
{
  return STATE::READY;
}

#endif
