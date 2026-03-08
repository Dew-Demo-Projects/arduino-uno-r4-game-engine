//
// Created by dew on 27.11.2025.
//

#include "TetrisBlock.h"

namespace UnoR4Matrix::Objects::Tetris {
    void TetrisBlock::setPosition(const Components::Position position) {
        _position = position;
    }

    std::vector<std::vector<size_t> > TetrisBlock::rotateShape90CW(
        const std::vector<std::vector<size_t> > &matrix) {
        if (matrix.empty()) return matrix;

        size_t oldHeight = matrix.size();
        size_t oldWidth = matrix[0].size();

        // New dimensions are swapped
        std::vector<std::vector<size_t> > rotated(oldWidth,
                                                  std::vector<size_t>(oldHeight));

        for (size_t i = 0; i < oldHeight; ++i) {
            for (size_t j = 0; j < oldWidth; ++j) {
                rotated[j][oldHeight - 1 - i] = matrix[i][j];
            }
        }

        return rotated;
    }

    std::vector<std::vector<size_t>> TetrisBlock::rotateShape90CCW(
    const std::vector<std::vector<size_t>>& matrix) {

        if (matrix.empty()) return matrix;

        size_t oldHeight = matrix.size();
        size_t oldWidth = matrix[0].size();

        std::vector<std::vector<size_t>> rotated(oldWidth,
                                               std::vector<size_t>(oldHeight));

        for (size_t i = 0; i < oldHeight; ++i) {
            for (size_t j = 0; j < oldWidth; ++j) {
                rotated[oldWidth - 1 - j][i] = matrix[i][j];
            }
        }

        return rotated;
    }

    void TetrisBlock::rotateClockwise() {
        const auto rotated = rotateShape90CW(getShape());
        setShape(rotated);
        std::swap(_width, _height);
    }

    void TetrisBlock::rotateCounterClockwise() {
        const auto rotated = rotateShape90CCW(getShape());
        setShape(rotated);
        std::swap(_width, _height);
    }
}
