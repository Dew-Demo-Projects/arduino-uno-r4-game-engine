//
// Created by dew on 26.11.2025.
//

#include "ObjectCore.h"

#include "../Components/Frame.h"

namespace UnoR4Matrix::Objects {
    ObjectCore::ObjectCore(const int id, const std::vector<std::vector<size_t> > &shape,
                           const Components::Position position)
        : _id{id}, _position{position} {
        if (shape.empty() || shape[0].empty()) {
            // Handle error or set default values
            _width = _height = 0;
            return;
        }
        _width = shape[0].size();
        _height = shape.size();
        _shape = shape;
    }

    void ObjectCore::draw(Components::Frame &frame) const {
        for (size_t i = 0; i < _height; ++i) {
            for (size_t j = 0; j < _width; ++j) {
                if (_shape[i][j]) {
                    const Components::Position pos(_position.X + j, _position.Y + i);
                    if (pos.X < Width && pos.Y < Height) {
                        frame.setPixel(pos, _shape[i][j]);
                    }
                }
            }
        }
    }

    Components::Position ObjectCore::getPosition() const {
        return _position;
    }

    void ObjectCore::setShape(const std::vector<std::vector<size_t> > &shape) {
        _shape = shape;
    }

    std::vector<std::vector<size_t> > ObjectCore::getShape() const {
        return _shape;
    }
}
