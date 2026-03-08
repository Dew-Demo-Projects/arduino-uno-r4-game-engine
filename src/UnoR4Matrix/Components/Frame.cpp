//
// Created by dew on 25.11.2025.
//

#include "../Core.h"
#include "Arduino.h"
#include "Frame.h"

#include <cstring>

#include "Position.h"

namespace UnoR4Matrix::Components {
    Frame::Frame() : _pixels{} {
        clear();
    }

    Frame::Frame(const uint8_t pixels[8][12]) : _pixels{} {
        setPixels(pixels);
    }

    Frame::Frame(const std::array<std::array<size_t, Height>, Width> &pixels) : _pixels{} {
        setPixels(pixels);
    }

    void Frame::clear() {
        // Initialize all pixels to 0
        for (auto &_pixel: _pixels) {
            for (unsigned char &x: _pixel) {
                x = 0;
            }
        }
        _dirty = true;
    }

    void Frame::setPixels(const std::array<std::array<size_t, Height>, Width> &newPixels) {
        // Convert from the old format to new format
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                _pixels[y][x] = newPixels[x][y] ? 1 : 0;
            }
        }
        _dirty = true;
    }

    void Frame::setPixels(const uint8_t pixels[Height][Width]) {
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                _pixels[y][x] = pixels[y][x];
            }
        }
        _dirty = true;
    }

    void Frame::setPixels(Frame &frame) {
        const uint8_t (*otherPixels)[Width] = frame.getPixels();
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                _pixels[y][x] = otherPixels[y][x];
            }
        }
        _dirty = true;
    }

    void Frame::setPixel(const Position position, const size_t value) {
        const size_t x = position.X;
        const size_t y = position.Y;

        if (!(x < Width && y < Height))
            return;

        uint8_t pixelValue = value ? 1 : 0;
        if (_pixels[y][x] == pixelValue)
            return;

        _pixels[y][x] = pixelValue;
        _dirty = true;

        // DEBUG
        // Serial.print("Pixel set at (");
        // Serial.print(x);
        // Serial.print(", ");
        // Serial.print(y);
        // Serial.print(") to ");
        // Serial.println(value);
    }

    size_t Frame::getPixel(const Position position) const {
        const size_t x = position.X;
        const size_t y = position.Y;

        if (x < Width && y < Height)
            return _pixels[y][x];
        return 0;
    }

    // Returns the pixel data in Arduino_LED_Matrix compatible format
    uint8_t (*Frame::getPixels())[Width] {
        return _pixels;
    }


    bool Frame::isDirty() const {
        return _dirty;
    }

    void Frame::markClean() {
        _dirty = false;
    }

    void Frame::markDirty() {
        _dirty = true;
    }

    bool Frame::operator==(const Frame &otherFrame) const {
        return std::memcmp(_pixels, otherFrame._pixels, sizeof(_pixels)) == 0;
    }
}
