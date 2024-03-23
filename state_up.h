#ifndef __STATES_UP_H
#define __STATES_UP_H

#include "state.h"
#include "bucket.h"

class UpState : public State
{
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool UpState::begin()
{
  log("UP", "UP");
  Bucket::setTarget(DESTINATION);

  return true; // no errors
}

bool UpState::run()
{
  Bucket::run();
  return true; // no errors
}

bool UpState::isDone()
{
  return Bucket::targetReached();
}

STATE UpState::nextState()
{
  return STATE::STOP;
}

#endif
