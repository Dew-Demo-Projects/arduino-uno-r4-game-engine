//
// Created by dew on 28.11.2025.
//

#include "InputHandler.h"
#include <Arduino.h>

namespace UnoR4Matrix::Input {
    InputHandler::InputHandler() : _lastKey(Key::UNDEFINED) {
    }

    void InputHandler::update() {
        if (Serial.available() > 0) {
            const char input = Serial.read();
            const Key key = parseSerialInput(input);

            if (key != Key::UNDEFINED) {
                _lastKey = key;

                // Trigger callback if set
                if (_keyCallback) {
                    _keyCallback(key);
                }

                // DEBUG
                // Serial.print("Key pressed: ");
                // switch (key) {
                //     case Key::A: Serial.println("A");
                //         break;
                //     case Key::D: Serial.println("D");
                //         break;
                //     case Key::S: Serial.println("S");
                //         break;
                //     case Key::Q: Serial.println("Q");
                //         break;
                //     case Key::E: Serial.println("E");
                //         break;
                //     case Key::SPACE: Serial.println("Space");
                //         break;
                //     case Key::P: Serial.println("{P}");
                //         break;
                //     default: break;
                // }
            }
        }
    }

    Key InputHandler::getLastKey() const {
        return _lastKey;
    }

    void InputHandler::clearLastKey() {
        _lastKey = Key::UNDEFINED;
    }

    void InputHandler::setKeyCallback(const KeyCallback &callback) {
        _keyCallback = callback;
    }

    Key InputHandler::parseSerialInput(const char input) {
        switch (input) {
            case 'a':
            case 'A': return Key::A;
            case 'd':
            case 'D': return Key::D;
            case 's':
            case 'S': return Key::S;
            case 'q':
            case 'Q': return Key::Q;
            case 'e':
            case 'E': return Key::E;
            case ' ': return Key::SPACE;
            case 'p':
            case 'P': return Key::P;
            default: return Key::UNDEFINED;
        }
    }
}
