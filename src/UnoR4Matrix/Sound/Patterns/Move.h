//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_MOVE_H
#define TETRIS_MOVE_H


#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Quick high blip
    inline constexpr Note Move[] = {{800, 10}, {0, 5}};
    inline constexpr size_t MoveLen = sizeof(Move) / sizeof(Move[0]);
}


#endif //TETRIS_MOVE_H
