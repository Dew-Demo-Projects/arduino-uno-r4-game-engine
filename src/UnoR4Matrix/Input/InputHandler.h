//
// Created by dew on 28.11.2025.
//

#ifndef TETRIS_INPUTHANDLER_H
#define TETRIS_INPUTHANDLER_H

#include <functional>

namespace UnoR4Matrix::Input {
    enum class Key {
        A,
        D,
        S,
        Q,
        E,
        SPACE,
        P,
        UNDEFINED
    };

    class InputHandler {
    public:
        InputHandler();

        void update(); // Read and process input
        [[nodiscard]] Key getLastKey() const; // Get the last pressed key
        void clearLastKey(); // Clear the last key

        // Callback system for key events
        using KeyCallback = std::function<void(Key)>;

        void setKeyCallback(const KeyCallback &callback);

    private:
        Key _lastKey;
        KeyCallback _keyCallback;

        Key parseSerialInput(char input);
    };
}

#endif //TETRIS_INPUTHANDLER_H
