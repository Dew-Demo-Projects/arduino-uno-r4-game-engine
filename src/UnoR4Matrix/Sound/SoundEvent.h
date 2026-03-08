//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_SOUNDEVENT_H
#define TETRIS_SOUNDEVENT_H
#pragma once

namespace UnoR4Matrix::Sound {
    enum class SoundEvent : unsigned char {
        Move,
        Rotate,
        SoftDrop,
        HardDrop,
        LineClear,
        LevelUp,
        PauseToggle,
        GameOver
    };
}

#endif //TETRIS_SOUNDEVENT_H
