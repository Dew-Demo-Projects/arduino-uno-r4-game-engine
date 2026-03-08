//
// Created by dew on 25.11.2025.
//

#include "Renderer.h"

#include <algorithm>
#include <Arduino.h>

#include "../Engines/EngineCore.h"
#include "../Objects/ObjectCore.h"

namespace UnoR4Matrix {
    void Renderer::begin(ArduinoLEDMatrix &matrix) {
        _matrix = &matrix;
        _matrix->begin();
    }

    void Renderer::setEngine(Engines::EngineCore *engine) {
        _engine = engine;
        _engine->start();
    }

    void Renderer::addObject(const std::shared_ptr<Objects::ObjectCore> &obj) {
        _objects.push_back(obj);
        _currFrame.markDirty();
    }

    void Renderer::removeObject(const std::shared_ptr<Objects::ObjectCore> &obj) {
        _objects.erase(
            std::remove_if(_objects.begin(), _objects.end(),
                           [&](const std::shared_ptr<Objects::ObjectCore> &o) { return o == obj; }),
            _objects.end()
        );
    }

    void Renderer::clearObjects() {
        _objects.clear();
    }

    bool Renderer::isFinished() const {
        return _engine ? _engine->isFinished() : true;
    }

    void Renderer::update() {
        if (!_engine) return;

        _prevFrame = _currFrame;
        _currFrame = _engine->update(_objects);
    }

    void Renderer::render() const {
        if (!_matrix) return;

        // Display the frame
        if (_prevFrame == _currFrame) return;
        displayFrame(_currFrame);
    }

    const std::vector<std::shared_ptr<Objects::ObjectCore> > &Renderer::getObjects() {
        return _objects;
    }

    const Components::Frame &Renderer::getCurrFrame() const {
        return _currFrame;
    }

    const Components::Frame &Renderer::getPrevFrame() const {
        return _prevFrame;
    }

    void Renderer::displayFrame(const Components::Frame &frame) const {
        uint8_t matrixFrame[8][12];
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 12; x++) {
                matrixFrame[y][x] = frame.getPixel(Components::Position(x, y)) ? 1 : 0;
            }
        }
        _matrix->renderBitmap(matrixFrame, 8, 12);
    }
}
