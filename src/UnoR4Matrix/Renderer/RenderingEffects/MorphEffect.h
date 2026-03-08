//
// Created by dew on 1.12.2025.
//

#ifndef TETRIS_MORPHEFFECT_H
#define TETRIS_MORPHEFFECT_H
#include <cstdint>

#include "UnoR4Matrix/Core.h"


namespace UnoR4Matrix::Components {
    class Frame;
}

class ArduinoLEDMatrix;

namespace UnoR4Matrix::Renderer::RenderingEffects {
    class MorphEffect {
    public:
        // steps  = number of interpolation steps
        // delayMs = delay between steps in milliseconds
        explicit MorphEffect(ArduinoLEDMatrix &matrix, int steps = 20, int delayMs = 40);

        void setSteps(int steps);

        void setDelayMs(int delayMs);

        // Main API
        void MorphFrames(Components::Frame &prevFrame, Components::Frame &currFrame);

    private:
        struct Pixel {
            int x;
            int y;
        };

        ArduinoLEDMatrix &_matrix;
        int _steps;
        int _delayMs;

        Pixel _startList[UnoR4Matrix::Pixels];
        Pixel _endList[UnoR4Matrix::Pixels];
        int _countA = 0;
        int _countB = 0;
        int _countN = 0;
        uint8_t _workFrame[UnoR4Matrix::Height][UnoR4Matrix::Width];

        // Helpers
        static int lerpInt(int a, int b, int s, int steps);

        static void buildPixelList(const uint8_t src[UnoR4Matrix::Height][UnoR4Matrix::Width],
                                   Pixel list[], int &count);

        void equalizeCounts(Pixel a[], int &countA,
                            Pixel b[], int &countB);

        void matchNearest(Pixel src[], Pixel dst[], int n);

        void clearWorkFrame();

        void displayWorkFrame();
    };
}

#endif //TETRIS_MORPHEFFECT_H
