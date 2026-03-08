//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_ISOUND_H
#define TETRIS_ISOUND_H

#pragma once
#include "SoundEvent.h"

namespace UnoR4Matrix::Sound {
    class ISound {
    public:
        virtual ~ISound() = default;

        virtual void begin() = 0;

        virtual void update() = 0; // call often from loop() (non-blocking)
        virtual void play(SoundEvent e) = 0;

        virtual void stop() = 0;

        [[nodiscard]] virtual bool isPlaying() const = 0;

        virtual void setMuted(bool muted) = 0;

        [[nodiscard]] virtual bool isMuted() const = 0;
    };
}

#endif //TETRIS_ISOUND_H
