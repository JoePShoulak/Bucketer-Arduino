#ifndef __MATRIX_H
#define __MATRIX_H

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#define WHITE 0xffffffff

struct Matrix {
	static ArduinoLEDMatrix matrix;

	static void begin() {
		matrix.begin();
		matrix.textFont(Font_5x7);
	}

	static void print(const String& text) {
		matrix.beginDraw();
		matrix.beginText(1, 1, WHITE);
		matrix.println(text);
		matrix.endText();
		matrix.endDraw();
	}
};

#endif
