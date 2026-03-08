#ifndef TETRIS_TETRISENGINE_H
#define TETRIS_TETRISENGINE_H

#include <memory>
#include <vector>

#include "UnoR4Matrix/Components/Frame.h"
#include "UnoR4Matrix/Engines/EngineCore.h"
#include "UnoR4Matrix/Objects/Tetris/TetrisBlockFactory.h"
#include "UnoR4Matrix/Objects/Tetris/TetrisBlock.h"

namespace UnoR4Matrix::Engines::TetrisEngine {
    class TetrisEngine : public EngineCore {
    public:
        TetrisEngine();

        ~TetrisEngine() override = default;

        void start() override;

        Components::Frame update(
            std::vector<std::shared_ptr<Objects::ObjectCore> > &objects) override;

        void handleInput(Input::Key key) override;

        // Game state accessors
        int getScore() const { return _score; }
        int getLevel() const { return _level; }
        int getLinesCleared() const { return _linesCleared; }
        bool isPaused() const { return _paused; }

    private:
        // Game board dimensions - Note: we're rotating the gameplay
        // Core.h defines Width=12, Height=8
        // For Tetris we want: BOARD_WIDTH = 8 (columns), BOARD_HEIGHT = 12 (rows)
        static constexpr int BOARD_ROWS = 12; // Tetris height
        static constexpr int BOARD_COLS = 8; // Tetris width

        // Game state
        bool _board[BOARD_ROWS][BOARD_COLS] = {false};
        std::shared_ptr<Objects::Tetris::TetrisBlock> _currentPiece;
        std::shared_ptr<Objects::Tetris::TetrisBlock> _nextPiece;
        int _score = 0;
        int _level = 1;
        int _linesCleared = 0;
        bool _gameOver = false;
        bool _paused = false;

        // Timing
        unsigned long _lastFallTime = 0;
        unsigned long _fallInterval = 1000; // Start at 1 second per fall
        unsigned long _lastInputTime = 0;
        static constexpr unsigned long INPUT_REPEAT_DELAY = 150;

        // Helper methods
        void reset();

        void spawnNewPiece();

        bool isValidPosition(const Objects::Tetris::TetrisBlock &piece) const;

        bool isValidPosition(const Objects::Tetris::TetrisBlock &piece, int dx, int dy) const;

        void lockPiece();

        int clearLines();

        void updateScore(int linesCleared);

        void updateLevel();

        void updateFallSpeed();

        void drawBoard(Components::Frame &frame) const;

        void drawPiece(Components::Frame &frame, const Objects::Tetris::TetrisBlock &piece) const;

        void movePiece(int dx, int dy);

        void rotatePiece(bool clockwise);

        void hardDrop();

        // Helper function for max
        template<typename T>
        T max(T a, T b) { return (a > b) ? a : b; }
    };
}

#endif // TETRIS_TETRISENGINE_H
