#include "thingProperties.h"
#include "matrixHelper.h"
#include "cloudHelper.h"
#include "stepperHelper.h"

#define BAUDRATE 9600

enum state
{
  BOOT,
  READY,
  UP,
  DOWN,
  STOP,
  ERROR
};

enum bucketPosition
{
  UNKNOWN,
  TOP,
  MIDDLE,
  BOTTOM
};

bool upRequested;
bool downRequested;
bool stopRequested;
String errorMsg;

state statePrev;
state stateCurr;
bucketPosition bucketPos;

void log(String serialMsg, String matrixMsg = "")
{
  if (matrixMsg == "")
    matrixMsg = serialMsg.substring(0, 2);

  message = serialMsg; // message is a cloud variable
  Serial.println(serialMsg);
  matrixPrint(matrixMsg);
}

void clearRequests()
{
  upRequested = false;
  downRequested = false;
  stopRequested = false;
}

void checkForStopRequests()
{
  if (stopRequested)
  {
    clearRequests();
    stateCurr = STOP;
  }
}

void checkForErrors()
{
  if (errorMsg.length > 0)
    stateCurr = ERROR;
}

void updateBucketPos(bucketPosition pos)
{
  bucketPos = pos;
  bucketRaised = pos == TOP;
  bucketLowered = pos == BOTTOM;
}

void startMovingToDestination(int destination)
{
  bucketInMotion = true;
  stepper.moveTo(-destination);
  updateBucketPos(MIDDLE);
}

void checkForDestinationReached(bucketPosition pos)
{
  if (!stepper.distanceToGo())
  {
    updateBucketPos(pos);
    stateCurr = STOP;
  }
}

void setup()
{
  matrixBegin();
  matrixPrint("BT");

  Serial.begin(BAUDRATE);
  cloudBegin();
  stepperBegin();

  checkForErrors();
  stateCurr = READY;
}

void readyState()
{
  // On transition to
  if (statePrev != stateCurr)
  {
    log("Ready!", "RD");
    statePrev = stateCurr;
  }

  // Main Function

  // Detect transition away
  checkForErrors();
  if (upRequested && bucketPos != TOP)
  {
    clearRequests();
    stateCurr = UP;
  }
  else if (downRequested && bucketPos != BOTTOM)
  {
    clearRequests();
    stateCurr = DOWN;
  }

  // On transition away
}

void upState()
{
  // On transition to
  if (statePrev != stateCurr)
  {
    log("UP");
    startMovingToDestination(DESTINATION);
    statePrev = stateCurr;
  }

  // Main Function
  stepper.run();

  // Detect transition away
  checkForErrors();
  checkForStopRequests();
  checkForDestinationReached(TOP);

  // On transition away
}

void downState()
{
  // On transition to
  if (statePrev != stateCurr)
  {
    log("DOWN", "DN");
    startMovingToDestination(-DESTINATION);
    statePrev = stateCurr;
  }

  // Main Function
  stepper.run();

  // Detect transition away
  checkForErrors();
  checkForStopRequests();
  checkForDestinationReached(BOTTOM);

  // On transition away
}

void stopState()
{
  // On transition to
  if (statePrev != stateCurr)
  {
    log("STOP", "ST");
    statePrev = stateCurr;
  }

  // Main Function
  bucketInMotion = false; // TODO: Actually stop the bucket

  // Detect transition away
  if (!bucketInMotion)
  {
    stateCurr = READY;
  }

  // On transition away
}

void errorState()
{
  if (statePrev != stateCurr)
  {
    log("Error: " + errorMsg, "ER");
    statePrev = stateCurr;
  }
}

void loop()
{
  ArduinoCloud.update();

  switch (stateCurr)
  {
  case READY:
    readyState();
    break;
  case UP:
    upState();
    break;
  case DOWN:
    downState();
    break;
  case STOP:
    stopState();
    break;
  default:
    errorState();
    break;
  }
}

void request(bool &ref)
{
  clearRequests();
  ref = true;
}

void onLowerBucketChange()
{
  if (lowerBucket)
    request(downRequested);
}

void onRaiseBucketChange()
{
  if (raiseBucket)
    request(upRequested);
}

void onStopBucketChange()
{
  if (stopBucket)
    request(stopRequested);
}

void onMessageChange()
{ // We don't care about messages sent to us
}
