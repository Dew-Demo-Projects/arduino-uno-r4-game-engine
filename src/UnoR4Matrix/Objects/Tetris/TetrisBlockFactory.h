//
// Created for Tetris block factory
//

#ifndef TETRIS_TETRISBLOCKFACTORY_H
#define TETRIS_TETRISBLOCKFACTORY_H

#include <memory>

#include "Bricks.h"
#include "TetrisBlock.h"

namespace UnoR4Matrix::Objects::Tetris {
    class TetrisBlockFactory {
    public:
        enum class BlockType {
            I, J, L, O, S, T, Z
        };

        static std::shared_ptr<TetrisBlock> createBlock(const BlockType type, const Components::Position& position) {
            switch (type) {
                case BlockType::I: return std::make_shared<IBlock>(position);
                case BlockType::J: return std::make_shared<JBlock>(position);
                case BlockType::L: return std::make_shared<LBlock>(position);
                case BlockType::O: return std::make_shared<OBlock>(position);
                case BlockType::S: return std::make_shared<SBlock>(position);
                case BlockType::T: return std::make_shared<TBlock>(position);
                case BlockType::Z: return std::make_shared<ZBlock>(position);
                default: return std::make_shared<TBlock>(position); // Default to T-block
            }
        }

        static std::shared_ptr<TetrisBlock> createRandomBlock(const Components::Position& position) {
            auto randomType = static_cast<BlockType>(random() % 7);
            return createBlock(randomType, position);
        }
    };
}

#endif //TETRIS_TETRISBLOCKFACTORY_H