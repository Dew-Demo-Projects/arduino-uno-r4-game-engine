//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_SOFTDROP_H
#define TETRIS_SOFTDROP_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Low thud
    inline constexpr Note SoftDrop[] = {{400, 15}, {0, 5}};
    inline constexpr size_t SoftDropLen = sizeof(SoftDrop) / sizeof(SoftDrop[0]);
}

#endif //TETRIS_SOFTDROP_H
