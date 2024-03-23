#ifndef __BUCKET_H
#define __BUCKET_H

#include <AccelStepper.h>
#include <MultiStepper.h>

#define STEPPER_MODE 1
#define PULSE_PIN 7
#define DIR_PIN 6
#define MAX_SPEED 100
#define MAX_ACCELERATION 20
#define DESTINATION 50

struct Bucket {
  static AccelStepper stepper(STEPPER_MODE, PULSE_PIN, DIR_PIN);

  static void begin() {
	stepper.setMaxSpeed(MAX_SPEED);
  	stepper.setAcceleration(MAX_ACCELERATION);
  }

  static void setTarget(int destination) {
	stepper.moveTo(-destination);
  }

  static bool targetReached() {
	return !stepper.distanceToGo();
	return true;
  }

  static void run() {
   if (!targetReached()) {
	stepper.run();
   }
  }
};

#endif
