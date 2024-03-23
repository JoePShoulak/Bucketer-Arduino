#ifndef __STATES_ERROR_H
#define __STATES_ERROR_H

#include "state.h"
#include "thingProperties.h"

class ErrorState : public State
{
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool ErrorState::begin()
{
  log("ERROR", "ER");
  error = true;
  return true; // no errors
}

bool ErrorState::run()
{
  return true; // no errors
}

bool ErrorState::isDone()
{
  return true;
}

STATE ErrorState::nextState()
{
  return STATE::ERROR;
}

#endif
