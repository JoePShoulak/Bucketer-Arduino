#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#define WHITE 0xffffffff

ArduinoLEDMatrix matrix;

void matrixBegin()
{
  matrix.begin();
  matrix.textFont(Font_5x7);
}

void matrixPrint(String text)
{
  matrix.beginDraw();
  matrix.beginText(1, 1, WHITE);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();
}
