#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#define WHITE 0xffffffff

void matrixPrint(ArduinoLEDMatrix &matrix, String text)
{
  matrix.beginDraw();
  matrix.beginText(1, 1, WHITE);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();
}
