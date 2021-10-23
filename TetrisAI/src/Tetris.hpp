#pragma once
#include "Stage.hpp"
#include "Block.hpp"
#include "Mino.hpp"
#include "Bag.hpp"

namespace Action {
    constexpr uint8
        MoveLeft               = 1 << 0,
        MoveRight              = 1 << 1,
        SoftDrop               = 1 << 2,
        HardDrop               = 1 << 3,
        RotateClockwise        = 1 << 4,
        RotateCounterclockwise = 1 << 5,
        Hold                   = 1 << 6;
}

class Tetris {
public:
    Tetris();
    ~Tetris();

    void init();

    bool update(uint8 action = 0);
    void draw() const;

private:
    void generate();

private:
    Stage m_stage;
    Mino m_currentMino;
    std::list<Mino> m_nextMinoes;

    Bag m_bag;

    int32 m_score;

};
