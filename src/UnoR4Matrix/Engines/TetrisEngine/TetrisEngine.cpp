#include "TetrisEngine.h"
#include <Arduino.h>
#include "GameInfoPrinter.h"
#include "UnoR4Matrix/Sound/ISound.h"

namespace UnoR4Matrix::Engines::TetrisEngine {
    TetrisEngine::TetrisEngine() {
        // Seed random with analog noise
        randomSeed(analogRead(0));
    }

    void TetrisEngine::start() {
        EngineCore::start();
        reset();
    }

    void TetrisEngine::reset() {
        // Clear board
        for (int y = 0; y < BOARD_ROWS; y++) {
            for (int x = 0; x < BOARD_COLS; x++) {
                _board[y][x] = false;
            }
        }

        _score = 0;
        _level = 1;
        _linesCleared = 0;
        _gameOver = false;
        _paused = false;
        _finished = false;

        _fallInterval = 1000;
        _lastFallTime = millis();
        _lastInputTime = millis();

        // Create first pieces
        _currentPiece = Objects::Tetris::TetrisBlockFactory::createRandomBlock(
            Components::Position(BOARD_COLS / 2 - 1, 0));
        _nextPiece = Objects::Tetris::TetrisBlockFactory::createRandomBlock(
            Components::Position(0, 0));
    }

    Components::Frame TetrisEngine::update(
        std::vector<std::shared_ptr<Objects::ObjectCore> > &objects) {
        // Update sound
        if (_sound) _sound->update();

        // Clear the frame
        objects.clear();

        // Read input buffer
        _inputHandler.update();

        if (_gameOver || _paused) {
            // Return current frame without updates
            Components::Frame frame;
            frame.clear();
            drawBoard(frame);
            if (!_gameOver && _paused) {
                // Draw pause indicator
                using Components::Position;
                // Draw 'P' for pause
                frame.setPixel(Position(5, 3), 1);
                frame.setPixel(Position(5, 4), 1);
                frame.setPixel(Position(5, 5), 1);
                frame.setPixel(Position(6, 3), 1);
                frame.setPixel(Position(6, 5), 1);
                frame.setPixel(Position(7, 3), 1);
                frame.setPixel(Position(7, 4), 1);
                frame.setPixel(Position(7, 5), 1);
            }
            return frame;
        }

        unsigned long currentTime = millis();

        // Handle automatic falling
        if (currentTime - _lastFallTime >= _fallInterval) {
            if (isValidPosition(*_currentPiece, 0, 1)) {
                movePiece(0, 1);
            } else {
                lockPiece();
                int lines = clearLines();
                if (lines > 0) {
                    updateScore(lines);
                    updateLevel();
                    if (_sound) {
                        // Pick sound based on event importance
                        if (lines >= 4) _sound->play(Sound::SoundEvent::LevelUp);
                        else _sound->play(Sound::SoundEvent::LineClear);
                    }
                }
                spawnNewPiece();
                if (!isValidPosition(*_currentPiece)) {
                    _gameOver = true;
                    _finished = true;
                }
            }
            _lastFallTime = currentTime;
        }

        // Create and draw frame
        Components::Frame frame;
        frame.clear();

        drawBoard(frame);
        drawPiece(frame, *_currentPiece);

        return frame;
    }

    void TetrisEngine::handleInput(Input::Key key) {
        if (_gameOver) {
            // Any key restarts when game over
            if (key != Input::Key::UNDEFINED) {
                start(); // Call start to reset
            }
            return;
        }

        unsigned long currentTime = millis();

        // Check for input repeat delay
        if (currentTime - _lastInputTime < INPUT_REPEAT_DELAY) {
            return;
        }

        switch (key) {
            case Input::Key::A: // Move left
                if (isValidPosition(*_currentPiece, -1, 0)) {
                    movePiece(-1, 0);
                    if (_sound) _sound->play(Sound::SoundEvent::Move);
                    _lastInputTime = currentTime;
                }
                break;

            case Input::Key::D: // Move right
                if (isValidPosition(*_currentPiece, 1, 0)) {
                    movePiece(1, 0);
                    if (_sound) _sound->play(Sound::SoundEvent::Move);
                    _lastInputTime = currentTime;
                }
                break;

            case Input::Key::S: // Move down (soft drop)
                if (isValidPosition(*_currentPiece, 0, 1)) {
                    movePiece(0, 1);
                    if (_sound) _sound->play(Sound::SoundEvent::SoftDrop);
                    // Add soft drop score
                    _score += 1;
                    _lastInputTime = currentTime;
                    _lastFallTime = currentTime; // Reset fall timer
                }
                break;

            case Input::Key::Q: // Rotate left
                rotatePiece(false);
                if (_sound) _sound->play(Sound::SoundEvent::Rotate);
                _lastInputTime = currentTime;
                break;

            case Input::Key::E: // Rotate right
                rotatePiece(true);
                if (_sound) _sound->play(Sound::SoundEvent::Rotate);
                _lastInputTime = currentTime;
                break;

            case Input::Key::SPACE: // Hard drop
                hardDrop();
                if (_sound) _sound->play(Sound::SoundEvent::HardDrop);
                _lastInputTime = currentTime;
                break;

            case Input::Key::P: // Pause
                _paused = !_paused;
                _lastInputTime = currentTime;
                if (_sound) _sound->play(Sound::SoundEvent::PauseToggle);
                break;

            default:
                break;
        }
    }

    void TetrisEngine::spawnNewPiece() {
        _currentPiece = _nextPiece;
        // Reset position to top center
        _currentPiece->setPosition(Components::Position(BOARD_COLS / 2 - 1, 0));

        // Generate new next piece using Arduino random
        _nextPiece = Objects::Tetris::TetrisBlockFactory::createRandomBlock(
            Components::Position(0, 0));
    }

    bool TetrisEngine::isValidPosition(const Objects::Tetris::TetrisBlock &piece) const {
        auto shape = piece.getShape();
        Components::Position pos = piece.getPosition();

        for (size_t y = 0; y < shape.size(); y++) {
            for (size_t x = 0; x < shape[y].size(); x++) {
                if (shape[y][x]) {
                    int boardX = pos.X + x;
                    int boardY = pos.Y + y;

                    // Check bounds
                    if (boardX < 0 || boardX >= BOARD_COLS || boardY >= BOARD_ROWS) {
                        return false;
                    }

                    // Don't check top bounds (allow pieces to spawn above visible area)
                    if (boardY >= 0 && _board[boardY][boardX]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool TetrisEngine::isValidPosition(const Objects::Tetris::TetrisBlock &piece, int dx, int dy) const {
        Components::Position newPos(piece.getPosition().X + dx, piece.getPosition().Y + dy);
        auto shape = piece.getShape();

        for (size_t y = 0; y < shape.size(); y++) {
            for (size_t x = 0; x < shape[y].size(); x++) {
                if (shape[y][x]) {
                    int boardX = newPos.X + x;
                    int boardY = newPos.Y + y;

                    // Check bounds
                    if (boardX < 0 || boardX >= BOARD_COLS || boardY >= BOARD_ROWS) {
                        return false;
                    }

                    // Don't check top bounds
                    if (boardY >= 0 && _board[boardY][boardX]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void TetrisEngine::lockPiece() {
        auto shape = _currentPiece->getShape();
        Components::Position pos = _currentPiece->getPosition();

        for (size_t y = 0; y < shape.size(); y++) {
            for (size_t x = 0; x < shape[y].size(); x++) {
                if (shape[y][x]) {
                    int boardX = pos.X + x;
                    int boardY = pos.Y + y;

                    if (boardY >= 0 && boardX >= 0 && boardX < BOARD_COLS && boardY < BOARD_ROWS) {
                        _board[boardY][boardX] = true;
                    }
                }
            }
        }
    }

    int TetrisEngine::clearLines() {
        int linesCleared = 0;

        for (int y = BOARD_ROWS - 1; y >= 0; y--) {
            bool lineComplete = true;
            for (int x = 0; x < BOARD_COLS; x++) {
                if (!_board[y][x]) {
                    lineComplete = false;
                    break;
                }
            }

            if (lineComplete) {
                // Remove this line
                for (int y2 = y; y2 > 0; y2--) {
                    for (int x = 0; x < BOARD_COLS; x++) {
                        _board[y2][x] = _board[y2 - 1][x];
                    }
                }

                // Clear top line
                for (int x = 0; x < BOARD_COLS; x++) {
                    _board[0][x] = false;
                }

                linesCleared++;
                y++; // Check the same line again (since we shifted down)
            }
        }

        _linesCleared += linesCleared;
        return linesCleared;
    }

    void TetrisEngine::updateScore(int linesCleared) {
        // Standard Tetris scoring
        switch (linesCleared) {
            case 1:
                _score += 100 * _level;
                break;
            case 2:
                _score += 300 * _level;
                break;
            case 3:
                _score += 500 * _level;
                break;
            case 4: // Tetris!
                _score += 800 * _level;
                break;
        }
    }

    void TetrisEngine::updateLevel() {
        // Level increases every 10 lines
        _level = 1 + (_linesCleared / 10);
        updateFallSpeed();
    }

    void TetrisEngine::updateFallSpeed() {
        // Speed increases with level (capped at minimum 100ms)
        _fallInterval = max(100, 1000 - (_level - 1) * 100);
    }

    void TetrisEngine::drawBoard(Components::Frame &frame) const {
        // Draw the board (rotated for display)
        // Board is 8x12 internally, but display is 12x8
        // We need to rotate: board[y][x] -> display[11-x][y]

        for (int y = 0; y < BOARD_ROWS; y++) {
            for (int x = 0; x < BOARD_COLS; x++) {
                if (_board[y][x]) {
                    // Rotate 90 degrees clockwise for display
                    // This maps our 8x12 board to the 12x8 display
                    int displayX = y; // Board row becomes display column
                    int displayY = 7 - x; // Board column becomes display row (flipped)

                    if (displayX >= 0 && displayX < Width && displayY >= 0 && displayY < Height) {
                        frame.setPixel(Components::Position(displayX, displayY), 1);
                    }
                }
            }
        }
    }

    void TetrisEngine::drawPiece(Components::Frame &frame, const Objects::Tetris::TetrisBlock &piece) const {
        auto shape = piece.getShape();
        Components::Position pos = piece.getPosition();

        for (size_t y = 0; y < shape.size(); y++) {
            for (size_t x = 0; x < shape[y].size(); x++) {
                if (shape[y][x]) {
                    int boardX = pos.X + x;
                    int boardY = pos.Y + y;

                    // Only draw if within visible area
                    if (boardY >= 0) {
                        // Rotate for display (same as board)
                        int displayX = boardY;
                        int displayY = 7 - boardX;

                        if (displayX >= 0 && displayX < Width && displayY >= 0 && displayY < Height) {
                            frame.setPixel(Components::Position(displayX, displayY), 1);
                        }
                    }
                }
            }
        }
    }

    void TetrisEngine::movePiece(int dx, int dy) {
        if (!_currentPiece) return;

        Components::Position newPos(
            _currentPiece->getPosition().X + dx,
            _currentPiece->getPosition().Y + dy
        );
        _currentPiece->setPosition(newPos);
    }

    void TetrisEngine::rotatePiece(bool clockwise) {
        if (!_currentPiece) return;

        // Save original state
        auto originalShape = _currentPiece->getShape();
        Components::Position originalPos = _currentPiece->getPosition();

        // Try rotation
        if (clockwise) {
            _currentPiece->Rotate90Right();
        } else {
            _currentPiece->Rotate90Left();
        }

        // If rotation causes collision, try wall kicks
        if (!isValidPosition(*_currentPiece)) {
            // Try moving right
            if (isValidPosition(*_currentPiece, 1, 0)) {
                movePiece(1, 0);
                return;
            }
            // Try moving left
            if (isValidPosition(*_currentPiece, -1, 0)) {
                movePiece(-1, 0);
                return;
            }
            // Try moving up (for pieces stuck at the bottom)
            if (isValidPosition(*_currentPiece, 0, -1)) {
                movePiece(0, -1);
                return;
            }

            // If all wall kicks fail, revert rotation
            _currentPiece->setShape(originalShape);
        }
    }

    void TetrisEngine::hardDrop() {
        if (!_currentPiece) return;

        int dropDistance = 0;
        while (isValidPosition(*_currentPiece, 0, dropDistance + 1)) {
            dropDistance++;
        }

        if (dropDistance > 0) {
            movePiece(0, dropDistance);
            lockPiece();

            // Score for hard drop: 2 points per cell dropped
            _score += dropDistance * 2;

            int lines = clearLines();
            if (lines > 0) {
                updateScore(lines);
                updateLevel();
            }

            spawnNewPiece();
            if (!isValidPosition(*_currentPiece)) {
                _gameOver = true;
                _finished = true;
            }
        }
    }
} // namespace UnoR4Matrix::Engines::TetrisEngine
