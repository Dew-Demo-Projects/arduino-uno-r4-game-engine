// UnoR4Matrix/Engines/TetrisEngine/TetrisGameRunner.h

#ifndef TETRIS_TETRISGAMERUNNER_H
#define TETRIS_TETRISGAMERUNNER_H

#include <Arduino_LED_Matrix.h>
#include "../../Renderer/Renderer.h"
#include "TetrisEngine.h"
#include "TetrisGameOverEngine.h"
#include "GameInfoPrinter.h"
#include "UnoR4Matrix/Sound/PassiveBuzzerSound.h"

namespace UnoR4Matrix::Engines::TetrisEngine {
    class TetrisGameRunner {
    public:
        explicit TetrisGameRunner(ArduinoLEDMatrix &matrix, const int buzzerPin)
            : _matrix(matrix),
              _state(State::PLAYING),
              _currEngine(&_mainEngine),
              _soundModule(buzzerPin) {
        }

        void begin() {
            Serial.begin(9600);
            while (!Serial) {
            }

            Serial.println("Starting Tetris Game...");
            GameInfoPrinter::printControls();

            _soundModule.begin();
            _renderer.begin(_matrix);
            _renderer.setEngine(_currEngine); // calls start() on _mainEngine

            _mainEngine.setSound(&_soundModule);
            _gameOverEngine.setSound(&_soundModule);

            delay(1000);
        }

        void run() {
            static unsigned long lastInfoUpdate = 0;
            const unsigned long now = millis();

            _renderer.update();
            _renderer.render();
            delay(16);

            // Optional: only print stats while playing
            if (_state == State::PLAYING &&
                now - lastInfoUpdate >= 2000) {
                GameInfoPrinter::printGameStats(
                    _mainEngine.getScore(),
                    _mainEngine.getLevel(),
                    _mainEngine.getLinesCleared()
                );
                lastInfoUpdate = now;
            }

            // Simple two‑state loop
            switch (_state) {
                case State::PLAYING:
                    if (_mainEngine.isFinished()) {
                        GameInfoPrinter::printGameOver(_mainEngine.getScore());
                        _state = State::GAME_OVER;
                        _currEngine = &_gameOverEngine;
                        _renderer.setEngine(_currEngine); // start() on game‑over engine
                    }
                    break;

                case State::GAME_OVER:
                    if (_gameOverEngine.isFinished()) {
                        // Just start a fresh TetrisEngine instance and go back to PLAYING
                        _mainEngine = TetrisEngine{};
                        _state = State::PLAYING;
                        _currEngine = &_mainEngine;
                        _renderer.setEngine(_currEngine); // start() on new main engine
                    }
                    break;
            }
        }

    private:
        enum class State { PLAYING, GAME_OVER };

        ArduinoLEDMatrix &_matrix;
        Renderer _renderer;
        State _state;

        EngineCore *_currEngine;
        TetrisEngine _mainEngine;
        TetrisGameOverEngine _gameOverEngine;
        Sound::PassiveBuzzerSound _soundModule;
    };
} // namespace UnoR4Matrix::Engines::TetrisEngine

#endif // TETRIS_TETRISGAMERUNNER_H
