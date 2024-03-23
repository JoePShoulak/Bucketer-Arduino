#ifndef __STATES_DOWN_H
#define __STATES_DOWN_H

#include "state.h"
#include "bucket.h"
#include "thingProperties.h"

class DownState : public State
{
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool DownState::begin()
{
  log("DOWN", "DN");
  Bucket::setTarget(-DESTINATION);
  bucketInMotion = true;
  bucketRaised = false;

  return true; // no errors
}

bool DownState::run()
{
  Bucket::run();
  return true; // no errors
}

bool DownState::isDone()
{
  return Bucket::targetReached();
}

STATE DownState::nextState()
{
  bucketLowered = true;
  return STATE::STOP;
}

#endif
