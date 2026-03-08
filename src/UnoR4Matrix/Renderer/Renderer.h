//
// Created by dew on 25.11.2025.
//

#ifndef TETRIS_UNOR4MATRIXRENDERER_H
#define TETRIS_UNOR4MATRIXRENDERER_H

#include "../Components/Frame.h"
#include <Arduino_LED_Matrix.h>
#include <vector>
#include <memory>

namespace UnoR4Matrix {
    namespace Objects {
        class ObjectCore;
    }

    namespace Engines {
        class EngineCore;
    }

    class Renderer {
    public:
        // Initialize with LED matrix
        void begin(ArduinoLEDMatrix &matrix);

        // Core methods
        void setEngine(Engines::EngineCore *engine);

        void addObject(const std::shared_ptr<Objects::ObjectCore> &obj);

        void removeObject(const std::shared_ptr<Objects::ObjectCore> &obj);

        // Additional control
        void clearObjects();

        [[nodiscard]] bool isFinished() const;

        void update(); // Runs engine logic and updates objects
        void render() const; // Draws all objects to the Frame

        const std::vector<std::shared_ptr<Objects::ObjectCore> > &getObjects();

        // Frame access
        [[nodiscard]] const Components::Frame &getCurrFrame() const;

        [[nodiscard]] const Components::Frame &getPrevFrame() const;

    private:
        void displayFrame(const Components::Frame &frame) const;

        Components::Frame _currFrame;
        Components::Frame _prevFrame;
        std::vector<std::shared_ptr<Objects::ObjectCore> > _objects;
        Engines::EngineCore *_engine = nullptr;
        ArduinoLEDMatrix *_matrix = nullptr;
    };
}


#endif //TETRIS_UNOR4MATRIXRENDERER_H
