#pragma once
#include <Arduino.h>
#include "ISound.h"
#include "Note.h"

namespace UnoR4Matrix::Sound {
    class PassiveBuzzerSound final : public ISound {
    public:
        explicit PassiveBuzzerSound(uint8_t pin) : _pin(pin) {
        }

        void begin() override;

        void update() override;

        void play(SoundEvent e) override;

        void stop() override;

        void setMuted(bool muted) override {
            _muted = muted;
            if (_muted) stop();
        }

        [[nodiscard]] bool isMuted() const override { return _muted; }

        [[nodiscard]] bool isPlaying() const override;

    private:
        static constexpr size_t QUEUE_CAP = 32;

        uint8_t _pin;
        bool _muted = false;

        // Ring buffer
        Note _queue[QUEUE_CAP]{};
        size_t _qHead = 0;
        size_t _qTail = 0;

        // Playback state
        bool _hasCurrent = false;
        unsigned long _currentEndsAt = 0;

        void enqueue(const Note &n);

        void enqueuePattern(const Note *notes, size_t len);

        bool dequeue(Note &out);

        void startNote(const Note &n);

        void clearQueue();
    };
}
