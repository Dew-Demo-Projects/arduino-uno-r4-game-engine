//
// Created by dew on 27.11.2025.
//

#ifndef TETRIS_ROTATABLE_H
#define TETRIS_ROTATABLE_H

namespace UnoR4Matrix::Objects::Interfaces {
    class IRotatable {
    public:
        virtual ~IRotatable() = default;

    public:
        virtual void Rotate90Left() = 0;
        virtual void Rotate90Right() = 0;
    };
}

#endif //TETRIS_ROTATABLE_H