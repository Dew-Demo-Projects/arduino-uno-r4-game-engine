//
// Created by dew on 26.11.2025.
//

#ifndef TETRIS_POSITION_H
#define TETRIS_POSITION_H
#include <cstdint>


namespace UnoR4Matrix::Components {
    class Position {
    public:
        Position(std::size_t x, std::size_t y);

        std::size_t X;
        std::size_t Y;
    };
}


#endif //TETRIS_POSITION_H
