//
// Created by dew on 27.11.2025.
//

#ifndef TETRIS_TETRISBLOCK_H
#define TETRIS_TETRISBLOCK_H

#include "../ObjectCore.h"

namespace UnoR4Matrix::Objects::Tetris {
    class TetrisBlock : public ObjectCore, public Interfaces::IRotatable {
    public:
        TetrisBlock(const int id, const std::vector<std::vector<size_t> > &shape,
                    const Components::Position position)
            : ObjectCore(id, shape, position) {
        }

        // IRotatable interface implementation
        void Rotate90Left() override {
            rotateCounterClockwise();
        }

        void Rotate90Right() override {
            rotateClockwise();
        }

        // Rotate 90 degrees clockwise
        void rotateClockwise();

        // Rotate 90 degrees counter-clockwise
        void rotateCounterClockwise();

        // Override getId from ObjectCore
        [[nodiscard]] int getId() const override { return _id; }

        void setPosition(Components::Position position);

    protected:
        // Helper function for 90-degree clockwise rotation
        [[nodiscard]] static std::vector<std::vector<size_t> > rotateShape90CW(
            const std::vector<std::vector<size_t> > &matrix);

        [[nodiscard]] static std::vector<std::vector<size_t> > rotateShape90CCW(
            const std::vector<std::vector<size_t> > &matrix);
    };
}

#endif //TETRIS_TETRISBLOCK_H
