#include "MorphEffect.h"
#include <Arduino.h>  // for random(), delay()
#include <Arduino_LED_Matrix.h>

#include "UnoR4Matrix/Components/Frame.h"

namespace UnoR4Matrix::Renderer::RenderingEffects {
    MorphEffect::MorphEffect(ArduinoLEDMatrix &matrix, int steps, int delayMs)
        : _matrix(matrix),
          _steps(steps),
          _delayMs(delayMs) {
        clearWorkFrame();
    }

    void MorphEffect::setSteps(int steps) {
        _steps = steps;
    }

    void MorphEffect::setDelayMs(int delayMs) {
        _delayMs = delayMs;
    }

    int MorphEffect::lerpInt(int a, int b, int s, int steps) {
        return (a * (steps - s) + b * s + steps / 2) / steps;
    }

    void MorphEffect::buildPixelList(const uint8_t src[Height][Width],
                                     Pixel list[], int &count) {
        count = 0;
        for (int y = 0; y < Height; ++y) {
            for (int x = 0; x < Width; ++x) {
                if (src[y][x]) {
                    list[count].x = x;
                    list[count].y = y;
                    ++count;
                }
            }
        }
    }

    void MorphEffect::equalizeCounts(Pixel a[], int &countA,
                                     Pixel b[], int &countB) {
        if (countA == 0 && countB == 0) {
            _countN = 0;
            return;
        }

        _countN = (countA > countB) ? countA : countB;

        while (countA < _countN) {
            int idx = random(countA);
            a[countA] = a[idx];
            ++countA;
        }

        while (countB < _countN) {
            int idx = random(countB);
            b[countB] = b[idx];
            ++countB;
        }
    }

    void MorphEffect::matchNearest(Pixel src[], Pixel dst[], int n) {
        static bool used[Pixels];
        static Pixel tmp[Pixels];

        for (int i = 0; i < n; ++i) {
            used[i] = false;
        }

        for (int i = 0; i < n; ++i) {
            int bestIdx = -1;
            int bestDist = 1000000;

            for (int j = 0; j < n; ++j) {
                if (used[j]) continue;

                int dx = src[i].x - dst[j].x;
                int dy = src[i].y - dst[j].y;
                int d2 = dx * dx + dy * dy;

                if (d2 < bestDist) {
                    bestDist = d2;
                    bestIdx = j;
                }
            }

            used[bestIdx] = true;
            tmp[i] = dst[bestIdx];
        }

        for (int i = 0; i < n; ++i) {
            dst[i] = tmp[i];
        }
    }

    void MorphEffect::clearWorkFrame() {
        for (int y = 0; y < Height; ++y) {
            for (int x = 0; x < Width; ++x) {
                _workFrame[y][x] = 0;
            }
        }
    }

    void MorphEffect::displayWorkFrame() {
        _matrix.renderBitmap(_workFrame, Height, Width);
    }

    void MorphEffect::MorphFrames(Components::Frame &prevFrame, Components::Frame &currFrame) {
        // Access underlying 2D pixel arrays from Frame
        const uint8_t (*fromPixels)[Width] = prevFrame.getPixels();
        const uint8_t (*toPixels)[Width] = currFrame.getPixels();

        buildPixelList(fromPixels, _startList, _countA);
        buildPixelList(toPixels, _endList, _countB);

        equalizeCounts(_startList, _countA, _endList, _countB);
        matchNearest(_startList, _endList, _countN);

        for (int s = 0; s <= _steps; ++s) {
            clearWorkFrame();

            for (int i = 0; i < _countN; ++i) {
                int x = lerpInt(_startList[i].x, _endList[i].x, s, _steps);
                int y = lerpInt(_startList[i].y, _endList[i].y, s, _steps);

                if (x >= 0 && x < Width && y >= 0 && y < Height) {
                    _workFrame[y][x] = 1;
                }
            }

            displayWorkFrame();
            delay(_delayMs);
        }
    }
} // namespace UnoR4Matrix::Components
