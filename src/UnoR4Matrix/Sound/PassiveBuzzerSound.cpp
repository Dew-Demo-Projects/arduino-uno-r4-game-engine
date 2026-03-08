#include "PassiveBuzzerSound.h"

// Include all pattern files
#include "Patterns/Move.h"
#include "Patterns/Rotate.h"
#include "Patterns/SoftDrop.h"
#include "Patterns/HardDrop.h"
#include "Patterns/LineClear.h"
#include "Patterns/LevelUp.h"
#include "Patterns/Pause.h"
#include "Patterns/GameOver.h"

namespace UnoR4Matrix::Sound {
    void PassiveBuzzerSound::begin() {
        pinMode(_pin, OUTPUT);
        noTone(_pin);
        clearQueue();
        _hasCurrent = false;
    }

    void PassiveBuzzerSound::update() {
        if (_muted) return;

        const unsigned long now = millis();

        // Check if current note/rest is finished
        if (_hasCurrent) {
            if ((long) (now - _currentEndsAt) >= 0) {
                _hasCurrent = false;
                noTone(_pin); // Stop sound immediately when time is up
            } else {
                return; // Still playing
            }
        }

        // Try to fetch next note
        Note next{};
        if (dequeue(next)) {
            startNote(next);
        }
    }

    void PassiveBuzzerSound::play(SoundEvent e) {
        if (_muted) return;

        // Interrupt long sounds for critical game events if desired
        if (e == SoundEvent::GameOver || e == SoundEvent::LineClear) {
            stop();
        }

        switch (e) {
                using namespace Patterns;
            case SoundEvent::Move: enqueuePattern(Move, MoveLen);
                break;
            case SoundEvent::Rotate: enqueuePattern(Rotate, RotateLen);
                break;
            case SoundEvent::SoftDrop: enqueuePattern(SoftDrop, SoftDropLen);
                break;
            case SoundEvent::HardDrop: enqueuePattern(HardDrop, HardDropLen);
                break;
            case SoundEvent::LineClear: enqueuePattern(LineClear, LineClearLen);
                break;
            case SoundEvent::LevelUp: enqueuePattern(LevelUp, LevelUpLen);
                break;
            case SoundEvent::PauseToggle: enqueuePattern(Pause, PauseLen);
                break;
            case SoundEvent::GameOver: enqueuePattern(GameOver, GameOverLen);
                break;
        }
    }

    void PassiveBuzzerSound::stop() {
        clearQueue();
        _hasCurrent = false;
        noTone(_pin);
    }

    bool PassiveBuzzerSound::isPlaying() const {
        if (_muted) return false;
        // Playing if we have a current note OR queue is not empty
        return _hasCurrent || (_qHead != _qTail);
    }

    void PassiveBuzzerSound::enqueue(const Note &n) {
        const size_t nextTail = (_qTail + 1) % QUEUE_CAP;
        if (nextTail == _qHead) {
            _qHead = (_qHead + 1) % QUEUE_CAP; // Drop oldest if full
        }
        _queue[_qTail] = n;
        _qTail = nextTail;
    }

    void PassiveBuzzerSound::enqueuePattern(const Note *notes, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            enqueue(notes[i]);
        }
    }

    bool PassiveBuzzerSound::dequeue(Note &out) {
        if (_qHead == _qTail) return false;
        out = _queue[_qHead];
        _qHead = (_qHead + 1) % QUEUE_CAP;
        return true;
    }

    void PassiveBuzzerSound::startNote(const Note &n) {
        _hasCurrent = true;
        _currentEndsAt = millis() + n.ms;

        if (n.freq > 0) {
            tone(_pin, n.freq);
        } else {
            noTone(_pin);
        }
    }

    void PassiveBuzzerSound::clearQueue() {
        _qHead = _qTail = 0;
    }
}
