// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[] = SECRET_SSID;          // Network SSID (name)
const char PASS[] = SECRET_OPTIONAL_PASS; // Network password (use for WPA, or use as key for WEP)

void onMessageChange();
void onLowerBucketChange();
void onRaiseBucketChange();
void onStopBucketChange();

String message;
bool bucketInMotion;
bool bucketLowered;
bool bucketRaised;
bool error;
bool lowerBucket;
bool raiseBucket;
bool stopBucket;

void initProperties()
{

  ArduinoCloud.addProperty(message, READWRITE, ON_CHANGE, onMessageChange);
  ArduinoCloud.addProperty(bucketInMotion, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(bucketLowered, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(bucketRaised, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(error, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(lowerBucket, READWRITE, ON_CHANGE, onLowerBucketChange);
  ArduinoCloud.addProperty(raiseBucket, READWRITE, ON_CHANGE, onRaiseBucketChange);
  ArduinoCloud.addProperty(stopBucket, READWRITE, ON_CHANGE, onStopBucketChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
