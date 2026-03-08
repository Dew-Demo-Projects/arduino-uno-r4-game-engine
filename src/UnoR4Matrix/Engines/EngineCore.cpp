//
// Created by dew on 26.11.2025.
//

#include "EngineCore.h"

namespace UnoR4Matrix::Engines {
    void EngineCore::start() {
        _inputHandler.setKeyCallback([this](const Input::Key key) {
            this->handleInput(key);
        });
    }

    bool EngineCore::isFinished() const {
        return _finished;
    }
}
