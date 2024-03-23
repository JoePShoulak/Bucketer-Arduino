#define DEBUG_LEVEL 2
#define CLOUD_DELAY 500

void cloudBegin()
{
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(DEBUG_LEVEL);
  ArduinoCloud.printDebugInfo();

  while (!ArduinoCloud.connected())
  {
    delay(CLOUD_DELAY);
    ArduinoCloud.update();
  }
}
