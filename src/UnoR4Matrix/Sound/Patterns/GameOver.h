//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_GAMEOVER_H
#define TETRIS_GAMEOVER_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Sad descending slide
    inline constexpr Note GameOver[] = {
        {1500, 150}, {1200, 150}, {900, 150}, {600, 300}, {0, 100}
    };
    inline constexpr size_t GameOverLen = std::size(GameOver);
}

#endif //TETRIS_GAMEOVER_H
