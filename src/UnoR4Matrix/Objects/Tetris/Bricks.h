//
// Created for Tetris block definitions
//

#ifndef TETRIS_TETRISBLOCKS_H
#define TETRIS_TETRISBLOCKS_H

#include "TetrisBlock.h"

namespace UnoR4Matrix::Objects::Tetris {

    // I-Block (cyan)
    class IBlock final : public TetrisBlock {
    public:
        explicit IBlock(const Components::Position& position)
            : TetrisBlock(1,
                         {{1, 1, 1, 1}},
                         position) {}
    };

    // J-Block (blue)
    class JBlock final : public TetrisBlock {
    public:
        explicit JBlock(const Components::Position& position)
            : TetrisBlock(2,
                         {{1, 0, 0},
                          {1, 1, 1}},
                         position) {}
    };

    // L-Block (orange)
    class LBlock final : public TetrisBlock {
    public:
        explicit LBlock(const Components::Position& position)
            : TetrisBlock(3,
                         {{0, 0, 1},
                          {1, 1, 1}},
                         position) {}
    };

    // O-Block (yellow)
    class OBlock final : public TetrisBlock {
    public:
        explicit OBlock(const Components::Position& position)
            : TetrisBlock(4,
                         {{1, 1},
                          {1, 1}},
                         position) {}
    };

    // S-Block (green)
    class SBlock final : public TetrisBlock {
    public:
        explicit SBlock(const Components::Position& position)
            : TetrisBlock(5,
                         {{0, 1, 1},
                          {1, 1, 0}},
                         position) {}
    };

    // T-Block (purple)
    class TBlock final : public TetrisBlock {
    public:
        explicit TBlock(const Components::Position& position)
            : TetrisBlock(6,
                         {{0, 1, 0},
                          {1, 1, 1}},
                         position) {}
    };

    // Z-Block (red)
    class ZBlock final : public TetrisBlock {
    public:
        explicit ZBlock(const Components::Position& position)
            : TetrisBlock(7,
                         {{1, 1, 0},
                          {0, 1, 1}},
                         position) {}
    };
}

#endif //TETRIS_TETRISBLOCKS_H