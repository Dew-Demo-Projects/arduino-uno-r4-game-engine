//
// Created by dew on 12.12.2025.
//

#ifndef TETRIS_NOTE_H
#define TETRIS_NOTE_H
#pragma once
#include <stdint.h>

namespace UnoR4Matrix::Sound {
    struct Note {
        uint16_t freq; // Frequency in Hz (0 = rest)
        uint16_t ms; // Duration in milliseconds
    };
}

#endif //TETRIS_NOTE_H
