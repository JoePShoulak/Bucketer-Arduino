#include "thingProperties.h"
#include "stateMachine.h"

StateMachine *stateMachine;

void setup()
{
  stateMachine = new StateMachine;
}

void loop()
{
  ArduinoCloud.update();
  stateMachine->run();
}

void onLowerBucketChange()
{
  if (lowerBucket && !bucketLowered)
    stateMachine->changeState(STATE::DOWN);
}

void onRaiseBucketChange()
{
  if (raiseBucket && !bucketRaised)
    stateMachine->changeState(STATE::UP);
}

void onStopBucketChange()
{
  if (stopBucket && bucketInMotion)
    stateMachine->changeState(STATE::STOP);
}

void onMessageChange()
{
  // We don't care about messages sent to us
}
