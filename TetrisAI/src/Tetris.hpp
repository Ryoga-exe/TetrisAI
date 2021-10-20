#pragma once
#include "Stage.hpp"
#include "Block.hpp"
#include "Mino.hpp"
#include "Bag.hpp"

enum class Action {
    None,
    MoveLeft,
    MoveRight,
    SoftDrop,
    HardDrop,
    RotateClockwise,
    RotateCounterclockwise,
    Hold,
};

class Tetris {
public:
    Tetris();
    ~Tetris();

    void init();

    bool update(Action action = Action::None);
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
