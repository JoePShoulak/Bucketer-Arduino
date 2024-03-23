#ifndef __STATES_STATE_H
#define __STATES_STATE_H

#include "matrix.h"
#include "thingProperties.h"

enum STATE
{
  BOOT,
  READY,
  UP,
  DOWN,
  STOP,
  ERROR,

  _TOTAL,
};

class State
{
protected:
  virtual void log(const String &a, const String &b) final;

public:
  virtual bool begin() = 0;
  virtual bool run() = 0;
  virtual bool isDone() = 0;
  virtual STATE nextState() = 0;
};

void State::log(const String &a, const String &b)
{
  message = a;
  Serial.print(a);
  Matrix::print(b);
}

#endif
