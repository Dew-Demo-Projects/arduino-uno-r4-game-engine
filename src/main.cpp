#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include "UnoR4Matrix/Engines/TetrisEngine/TetrisGameRunner.h"

using namespace UnoR4Matrix::Engines::TetrisEngine;

// Global variables
ArduinoLEDMatrix matrix;
TetrisGameRunner gameRunner(matrix, 13);

void setup() {
    gameRunner.begin();
}

void loop() {
    gameRunner.run();
}
