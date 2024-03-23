//#include "thingProperties.h"
#include "cloudHelper.h"
#include "stateMachine.h"

#define BAUDRATE 9600

bool upRequested;
bool downRequested;
bool stopRequested;
String errorMsg;

StateMachine* state_machine;

void setup()
{
  state_machine = new StateMachine;
}

void loop()
{
  ArduinoCloud.update();
  state_machine->run();
}

void request(bool &ref)
{
  clearRequests();
  ref = true;
}

void onLowerBucketChange()
{
  if (lowerBucket)
    state_machine->changeState(STATE::DOWN);
}

void onRaiseBucketChange()
{
  if (raiseBucket)
    state_machine->changeState(STATE::UP);
}

void onStopBucketChange()
{
  if (stopBucket)
    state_machine->changeState(STATE::STOP);
}

void onMessageChange()
{ // We don't care about messages sent to us
}
