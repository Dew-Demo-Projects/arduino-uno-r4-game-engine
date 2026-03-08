//
// Created by dew on 26.11.2025.
//

#ifndef TETRIS_OBJECT_H
#define TETRIS_OBJECT_H

#include <array>
#include <vector>
#include "../Components/Position.h"
#include "Interfaces/IRotatable.h"

namespace UnoR4Matrix::Components {
    class Frame;
}

namespace UnoR4Matrix::Objects {
    class ObjectCore {
    public:
        ObjectCore(int id, const std::vector<std::vector<size_t> > &shape, Components::Position position);

        virtual ~ObjectCore() = default;

        void draw(Components::Frame &frame) const;


        [[nodiscard]] virtual int getId() const { return -1; }

        [[nodiscard]] Components::Position getPosition() const;

        void setShape(const std::vector<std::vector<size_t> > &shape);

        [[nodiscard]] std::vector<std::vector<size_t> > getShape() const;

    protected:
        int _id;
        Components::Position _position;
        std::size_t _width;
        std::size_t _height;
        std::vector<std::vector<size_t> > _shape;
    };
}

#endif //TETRIS_OBJECT_H
