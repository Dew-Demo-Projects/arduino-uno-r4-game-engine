//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_LEVELUP_H
#define TETRIS_LEVELUP_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Triumphant scale
    inline constexpr Note LevelUp[] = {
        {1046, 60}, {1318, 60}, {1568, 60}, {2093, 60}, {2637, 100}, {0, 50}
    };
    inline constexpr size_t LevelUpLen = sizeof(LevelUp) / sizeof(LevelUp[0]);
}

#endif //TETRIS_LEVELUP_H
