//
// Created by dew on 26.11.2025.
//

#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H
#include <memory>
#include <vector>

#include "../Objects/ObjectCore.h"
#include "UnoR4Matrix/Input/InputHandler.h"

namespace UnoR4Matrix::Sound {
    class ISound;
}

namespace UnoR4Matrix::Components {
    class Frame;
}

namespace UnoR4Matrix::Engines {
    class EngineCore {
    public:
        virtual ~EngineCore() = default;

        virtual void start();

        void setSound(Sound::ISound *sound) { _sound = sound; }

        virtual Components::Frame update(std::vector<std::shared_ptr<Objects::ObjectCore> > &) = 0;

        [[nodiscard]] virtual bool isFinished() const;


        virtual void handleInput(Input::Key key) = 0;

    protected:
        bool _finished = false;
        Input::InputHandler _inputHandler;
        Sound::ISound *_sound = nullptr;
    };
}


#endif //TETRIS_ENGINE_H
