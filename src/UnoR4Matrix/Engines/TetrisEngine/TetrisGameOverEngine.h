// UnoR4Matrix/Engines/TetrisEngine/TetrisGameOverEngine.h

#ifndef TETRIS_GAMEOVEREFFECT_H
#define TETRIS_GAMEOVEREFFECT_H

#include <memory>
#include <vector>

#include "UnoR4Matrix/Components/Frame.h"
#include "UnoR4Matrix/Engines/EngineCore.h"
#include "UnoR4Matrix/Input/InputHandler.h"
#include "UnoR4Matrix/Objects/ObjectCore.h"
#include "Arduino.h"
#include "UnoR4Matrix/Sound/ISound.h"

namespace UnoR4Matrix::Engines::TetrisEngine {
    class TetrisGameOverEngine final : public EngineCore {
    public:
        TetrisGameOverEngine()
            : _step(0),
              _lastStepTime(0) {
        }

        ~TetrisGameOverEngine() override = default;

        void start() override {
            EngineCore::start();
            if (_sound) _sound->play(Sound::SoundEvent::GameOver);

            _finished = false; // Reset the base class flag
            _step = 0;
            _lastStepTime = millis();
        }

        Components::Frame update(
            std::vector<std::shared_ptr<Objects::ObjectCore> > &objects) override {
            if (_sound) _sound->update();

            objects.clear();

            // Read input buffer
            _inputHandler.update();

            const unsigned long now = millis();
            constexpr unsigned long stepInterval = 120;

            if (now - _lastStepTime >= stepInterval) {
                _lastStepTime = now;
                _step = (_step + 1) % 32;
            }

            Components::Frame frame;
            frame.clear();

            drawStaticIcon(frame);
            drawMovingWave(frame, _step);

            return frame;
        }

        void handleInput(const Input::Key key) override {
            (void) key;
            if (millis() - _lastStepTime >= 1000) {
                _finished = true; // Only need to set this
            }
        }

    private:
        uint8_t _step;
        unsigned long _lastStepTime;

        static void drawStaticIcon(Components::Frame &frame) {
            using Components::Position;

            const Position pixels[] = {
                {3, 2}, {4, 2}, {7, 2}, {8, 2},
                {4, 3}, {5, 3}, {6, 3}, {7, 3},
                {4, 4}, {5, 4}, {6, 4}, {7, 4},
                {3, 5}, {4, 5}, {7, 5}, {8, 5}
            };

            for (const auto &p: pixels) {
                frame.setPixel(p, 1);
            }
        }

        static void drawMovingWave(Components::Frame &frame, uint8_t step) {
            using Components::Position;
            constexpr int width = Width;
            constexpr int height = Height;

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    if (((x + y + step) % 4) == 0) {
                        frame.setPixel(Position(x, y), 1);
                    }
                }
            }
        }
    };
}

#endif // TETRIS_GAMEOVEREFFECT_H
