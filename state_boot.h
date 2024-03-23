#ifndef __STATES_SETUP_H
#define __STATES_SETUP_H

#include "state.h"
#include "matrix.h"

#define BAUDRATE 9600

class BootState : public State
{
public:
  bool begin() override;
  bool run() override;
  bool isDone() override;
  STATE nextState() override;
};

bool BootState::begin()
{
  Matrix::begin();
  Matrix::print("BT");

  Serial.begin(BAUDRATE);
  cloudBegin();
  Bucket::begin();

  return true; // no errors
}

bool BootState::run()
{
  return true; // no errors
}

bool BootState::isDone()
{
  return true;
}

STATE BootState::nextState()
{
  return STATE::READY;
}

#endif
