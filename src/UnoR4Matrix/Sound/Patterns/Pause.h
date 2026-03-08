//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_PAUSE_H
#define TETRIS_PAUSE_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Two-tone toggle
    inline constexpr Note Pause[] = {{600, 80}, {800, 80}, {0, 50}};
    inline constexpr size_t PauseLen = sizeof(Pause) / sizeof(Pause[0]);
}

#endif //TETRIS_PAUSE_H
