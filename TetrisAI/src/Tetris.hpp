#pragma once
#include "Stage.hpp"
#include "Block.hpp"
#include "Mino.hpp"
#include "Bag.hpp"

class Tetris {
public:
    Tetris();
    ~Tetris();

    void init();

    bool update();
    void draw() const;
private:
    Stage m_stage;
    Mino m_currentMino;
    Array<Mino> m_nextMinoes;

    Bag m_bag;

};
