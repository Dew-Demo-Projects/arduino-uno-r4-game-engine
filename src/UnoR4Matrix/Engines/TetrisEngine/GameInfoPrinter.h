//
// Created by dew on 1.12.2025.
//

#ifndef TETRIS_GAMEINFOPRINTER_H
#define TETRIS_GAMEINFOPRINTER_H

#include <Arduino.h>

namespace UnoR4Matrix::Engines::TetrisEngine {
    class GameInfoPrinter {
    public:
        static void printControls() {
            Serial.println("Controls:");
            Serial.println("  A/D - Move left/right");
            Serial.println("  S   - Move down");
            Serial.println("  Q/E - Rotate left/right");
            Serial.println("  Space - Hard drop");
            Serial.println("  P   - Pause");
        }

        static void printGameStats(int score, int level, int linesCleared) {
            Serial.println("=== TETRIS GAME ===");
            Serial.print("Score: ");
            Serial.println(score);
            Serial.print("Level: ");
            Serial.println(level);
            Serial.print("Lines: ");
            Serial.println(linesCleared);
            Serial.println("================");
        }

        static void printGameOver(int finalScore) {
            Serial.println("!!! GAME OVER !!!");
            Serial.print("Final Score: ");
            Serial.println(finalScore);
        }
    };
}

#endif // TETRIS_GAMEINFOPRINTER_H
