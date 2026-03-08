//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_ROTATE_H
#define TETRIS_ROTATE_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Quick rising chirp
    inline constexpr Note Rotate[] = {{1200, 15}, {0, 5}};
    inline constexpr size_t RotateLen = sizeof(Rotate) / sizeof(Rotate[0]);
}

#endif //TETRIS_ROTATE_H
