//
// Created by dew on 25.11.2025.
//

#ifndef TETRIS_UNOR4MATRIXUTILS_H
#define TETRIS_UNOR4MATRIXUTILS_H

#include <array>
#include "../Core.h"
#include "Position.h"

namespace UnoR4Matrix::Components {
    class Position;
}

namespace UnoR4Matrix::Components {
    class Frame {
    public:
        Frame();

        explicit Frame(const uint8_t pixels[Height][Width]);

        explicit Frame(const std::array<std::array<size_t, Height>, Width> &pixels);

        void clear();

        void setPixels(const std::array<std::array<size_t, Height>, Width> &newPixels); // Left for compatibility
        void setPixels(const uint8_t pixels[Height][Width]);

        void setPixels(Frame &frame);

        void setPixel(Position position, size_t value);

        [[nodiscard]] size_t getPixel(Position position) const;

        // Direct access to Arduino LED Matrix compatible data
        [[nodiscard]] uint8_t (*getPixels())[12];

        [[nodiscard]] bool isDirty() const;

        void markClean();

        void markDirty();

        bool operator==(const Frame &otherFrame) const;

    private:
        uint8_t _pixels[Height][Width];
        bool _dirty = true;
    };
};


#endif //TETRIS_UNOR4MATRIXUTILS_H
