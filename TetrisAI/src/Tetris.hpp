#pragma once
#include "Stage.hpp"
#include "Block.hpp"
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
    Bag m_bag;
};
