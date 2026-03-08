//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_HARDDROP_H
#define TETRIS_HARDDROP_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Fast high-to-low slide (two notes)
    inline constexpr Note HardDrop[] = {{800, 20}, {300, 40}, {0, 20}};
    inline constexpr size_t HardDropLen = sizeof(HardDrop) / sizeof(HardDrop[0]);
}

#endif //TETRIS_HARDDROP_H
