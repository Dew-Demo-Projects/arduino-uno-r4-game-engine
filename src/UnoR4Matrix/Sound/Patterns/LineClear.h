//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_LINECLEAR_H
#define TETRIS_LINECLEAR_H
#pragma once
#include "../Note.h"
#include <cstddef>

namespace UnoR4Matrix::Sound::Patterns {
    // Classic success arpeggio
    inline constexpr Note LineClear[] = {
        {1318, 50}, {1568, 50}, {1760, 50}, {2093, 80}, {0, 50}
    };
    inline constexpr size_t LineClearLen = sizeof(LineClear) / sizeof(LineClear[0]);
}

#endif //TETRIS_LINECLEAR_H
