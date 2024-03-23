#ifndef __STATES_STATE_H
#define __STATES_STATE_H

#include "matrix.h"

enum STATE {
  SETUP,
  READY,
  UP,
  DOWN,
  STOP,
  ERROR,

  _TOTAL,
};

class State {
protected:
  virtual void log(const String& a, const String& b) final;

public:
  virtual bool begin() = 0;
  virtual bool run() = 0;
  virtual bool isDone() = 0;
  virtual STATE nextState() = 0;
};

void State::log(const  String&a, const String& b) {
  Matrix::print(a + ': ' + b);
}

#endif
