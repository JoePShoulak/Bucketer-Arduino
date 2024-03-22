#include <AccelStepper.h>
#include <MultiStepper.h>
#include "thingProperties.h"
#include "matrixHelper.h"

#define DEBUG_LEVEL 2
#define BAUDRATE 9600
#define SERIAL_DELAY 1500
#define CLOUD_DELAY 500

/* Stepper */
#define STEPPER_MODE 1
#define PULSE_PIN 7
#define DIR_PIN 6
#define MAX_SPEED 100
#define MAX_ACCELERATION 20
#define DESTINATION 500

AccelStepper stepper(STEPPER_MODE, PULSE_PIN, DIR_PIN);
ArduinoLEDMatrix matrix;

bool upRequested;
bool downRequested;
bool stopRequested;

void log(String serialMsg, String matrixMsg = "") {
  if (matrixMsg == "") matrixMsg = serialMsg.substring(0, 2);

  message = serialMsg;
  Serial.println(serialMsg);
  matrixPrint(matrix, matrixMsg);
}

enum state {
  BOOT,
  READY,
  UP,
  DOWN,
  STOP,
  ERROR
};

enum bucketPosition {
  UNKNOWN,
  TOP,
  MIDDLE,
  BOTTOM
};

state statePrev;
state stateCurr;
bucketPosition bucketPos;

void setup()
{
  Serial.begin(BAUDRATE);
  
  matrix.begin();
  matrix.textFont(Font_5x7);
  
  log("Booting...", "BT");
  
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(DEBUG_LEVEL);
  ArduinoCloud.printDebugInfo();
  
  while (!ArduinoCloud.connected()) {
    ArduinoCloud.update();
    delay(CLOUD_DELAY);
  }

  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(MAX_ACCELERATION);
  stepper.moveTo(DESTINATION);

  stateCurr = READY;
}

void readyState() {
  // On transition to
  if (statePrev != stateCurr) {
    log("Ready!", "RD");
    bucketInMotion = false;
    statePrev = stateCurr;
  }

  // Main Function
  if (!stepper.distanceToGo())
    stepper.moveTo(-stepper.currentPosition());

  // Detect transition away
  if (upRequested) {
    stateCurr = UP;
  } else if (downRequested) {
    stateCurr = DOWN;
  }

  // On transition away
}

void upState() {
  // On transition to
  if (statePrev != stateCurr) {
    log("UP");
    bucketInMotion = true;
    statePrev = stateCurr;
  }

  // Main Function

  // Detect transition away
  if (stopRequested) {
    stateCurr = STOP;
  }

  // On transition away
}

void downState() {
  // On transition to
  if (statePrev != stateCurr) {
    log("DOWN", "DN");
    bucketInMotion = true;
    statePrev = stateCurr;
  }

  // Main Function

  // Detect transition away
  if (stopRequested) {
    stateCurr = STOP;
  }

  // On transition away
}

void stopState() {
  // On transition to
  if (statePrev != stateCurr) {
    log("STOP", "ST");
    bucketInMotion = false;
    statePrev = stateCurr;
  }

  // Main Function

  // Detect transition away
  if (!bucketInMotion) {
    stateCurr = READY;
  }
  
  // On transition away
}

void errorState() {
  // On transition to
  if (statePrev != stateCurr) {
    log("Error!", "ER");
    statePrev = stateCurr;
  }

  // Main Function

  // No transition away
}

void loop()
{
  ArduinoCloud.update();

  switch (stateCurr) {
    case READY:
      readyState();
      break;
    case UP:
      upState();
      break;
    case DOWN:
      downState();
      break;
    default:
      errorState();
      break;
  }
}

void clearRequests() {
  upRequested = false;
  downRequested = false;
  stopRequested = false;
}

void onLowerBucketChange()  {
  if (!lowerBucket) return;
  
  clearRequests();
  downRequested = true;
}

void onRaiseBucketChange()  {
  if (!raiseBucket) return;
  
  clearRequests();
  upRequested = true;
}

void onStopBucketChange()  {
  if (!stopBucket) return;
  
  clearRequests();
  stopRequested = true;
}

void onMessageChange() {
  
}
